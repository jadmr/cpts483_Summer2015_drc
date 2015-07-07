
#include "DRCClient.h"
#include "ui_DRCClient.h"
#include "mpfilemaker.h"


// GUI STUFF
#include <QGridLayout>
#include <QTabWidget>
#include "loginform.h"
#include "queryform.h"
#include "Mediator.h"
#include "drctypes.h"
#include "toolbarmanager.h"
#include "mediationbrowser.h"
#include "mptoolbox.h"
#include "mainmenuform.h"
#include "manageusers.h"
#include "mediationevaluationview.h"
#include "reswareportform.h"
#include "slideshowform.h"
#include "monthlyreportform.h"
#include "tabbedbrowsers.h"
#include "slotsgame.h"

// DRC COMPONENTS
#include "drcbl.h"
#include "drcdb.h"

// MISC
#include <QDebug>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>

const QString DBPATH_FILE = "dbpath.txt";
const QString DB_DEFAULT_PATH = "drc_db.db3";


DRCClient::DRCClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DRCClient)
    , _browserDock(nullptr)
{
    ui->setupUi(this);
    // set up a seed for any random numbers generated with qrand()
    qsrand( QDateTime::currentMSecsSinceEpoch()/1000);
    closeNote = true;
    // Check for a saved database path... Load the default otherwise.
    _db.LoadDatabase(LoadDBPathFromFile());
    _notesChanged = false;
    _mediationProcessVector = new MediationProcessVector();
    _mediationProcessView = nullptr;
    // Set the window to max size.
    this->setWindowState(Qt::WindowMaximized);
    setCentralWidget(new LoginForm(this));

    // Listen for Events
    _unregEnableMenusCall = Mediator::Register(MKEY_GUI_ENABLE_MENUS, [this](MediatorArg arg){Q_UNUSED(arg);ShowMainMenu();});
    _unregDisableMenusCall = Mediator::Register(MKEY_GUI_DISABLE_MENUS, [this](MediatorArg arg){Q_UNUSED(arg);SetMenuBarDisabled();SetMenuHelpDisabled();});
    _unregShowAdminCall = Mediator::Register(MKEY_GUI_SHOW_ADMIN, [this](MediatorArg arg){Q_UNUSED(arg);SetMenuAdminShow();});
    _unregHideAdminCall = Mediator::Register(MKEY_GUI_HIDE_ADMIN, [this](MediatorArg arg){Q_UNUSED(arg);SetMenuAdminHide();});
    _unregShowMediationBrowserCall = Mediator::Register(MKEY_GUI_SHOW_MEDIATION_BROWSER, [this](MediatorArg arg){Q_UNUSED(arg);ShowMediationBrowser();});
    _unregShowSessionsBrowserCall = Mediator::Register(MKEY_GUI_SHOW_SESSIONS_BROWSER, [this](MediatorArg arg){Q_UNUSED(arg);ShowSessionBrowser();});
    _unregShowNotesBrowserCall = Mediator::Register(MKEY_GUI_SHOW_NOTES_BROWSER, [this](MediatorArg arg){ShowNotesBrowser(arg);});
    _unregMpNewformCall = Mediator::Register(MKEY_GUI_MP_NEW_FORM, [this](MediatorArg arg){Q_UNUSED(arg);LoadMediationProcessView();});
    _unregShowEvalCall = Mediator::Register(MKEY_GUI_SHOW_EVALUATION, [this](MediatorArg arg){Q_UNUSED(arg);LoadEvaluationView();});
    _unregShowMonthlyCall = Mediator::Register(MKEY_GUI_SHOW_MONTHLY_REPORT, [this](MediatorArg arg){Q_UNUSED(arg);ShowMonthlyReport();});
    _unregShowReswaCall = Mediator::Register(MKEY_GUI_SHOW_RESWA_REPORT, [this](MediatorArg arg){Q_UNUSED(arg);ShowResWaReport();});
    _unregNoteChanged = Mediator::Register(MKEY_GUI_NOTE_CHANGED, [this](MediatorArg arg){Notes_Changed(arg);});

    // Toolbar manager setup
    ToolbarManager::Instance().SetToolbar(ui->toolBar);
    ToolbarManager::Instance().Clear();

    // Disable Menus Until Logged In
    SetMenusEnabled(false, false);
}

DRCClient::~DRCClient()
{
   delete ui;
   Mediator::Unregister(MKEY_GUI_ENABLE_MENUS, _unregEnableMenusCall);
   Mediator::Unregister(MKEY_GUI_DISABLE_MENUS, _unregDisableMenusCall);
   Mediator::Unregister(MKEY_GUI_SHOW_ADMIN, _unregShowAdminCall);
   Mediator::Unregister(MKEY_GUI_HIDE_ADMIN, _unregHideAdminCall);
   Mediator::Unregister(MKEY_GUI_SHOW_MEDIATION_BROWSER, _unregShowMediationBrowserCall);
   Mediator::Unregister(MKEY_GUI_SHOW_SESSIONS_BROWSER, _unregShowSessionsBrowserCall);
   Mediator::Unregister(MKEY_GUI_SHOW_NOTES_BROWSER, _unregShowNotesBrowserCall);
   Mediator::Unregister(MKEY_GUI_MP_NEW_FORM, _unregMpNewformCall);
   Mediator::Unregister(MKEY_GUI_SHOW_EVALUATION, _unregShowEvalCall);
   Mediator::Unregister(MKEY_GUI_SHOW_MONTHLY_REPORT, _unregShowMonthlyCall);
   Mediator::Unregister(MKEY_GUI_SHOW_RESWA_REPORT, _unregShowReswaCall);
   Mediator::Unregister(MKEY_GUI_NOTE_CHANGED, _unregNoteChanged);
}

void DRCClient::SetMenusEnabled(bool enableMenus, bool showAdmin)
{
    ui->menuBar->setEnabled(enableMenus);
    ui->toolBar->setEnabled(enableMenus);
    ui->menuAdmin->menuAction()->setVisible(showAdmin);
}

void DRCClient::SetMenuBarEnabled()
{
    ui->menuBar->setEnabled(true);
    ui->toolBar->setEnabled(true);
}

void DRCClient::SetMenuHelpEnabled()
{
//    ui->menuHelp->setEnabled(true);
}

void DRCClient::SetMenuBarDisabled()
{
    ui->menuBar->setEnabled(false);
}

void DRCClient::SetMenuHelpDisabled()
{
//    ui->menuHelp->setEnabled(false);
}

void DRCClient::SetMenuAdminShow()
{
    ui->menuAdmin->menuAction()->setVisible(true);
}

void DRCClient::SetMenuAdminHide()
{
    ui->menuAdmin->menuAction()->setVisible(false);
}


void DRCClient::on_actionNew_search_form_triggered()
{
 //   setCentralWidget(new SearchWizard(this));
    setCentralWidget(new QueryForm(this));
}

void DRCClient::on_actionOpen_mediation_view_triggered()
{
    if(_mediationProcessView && _mediationProcessView->getChangesPending())
    {
        if(_notesChanged)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to create new?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    LoadMediationProcessView();
                    _notesChanged = false;
                }
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to create new?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                LoadMediationProcessView();

            }
        }
    }
    else if(_mediationProcessView && _notesChanged)
    {
        QMessageBox msgBox;
        QString strsda;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            LoadMediationProcessView();
            _notesChanged = false;
        }
    }
    else
       LoadMediationProcessView();
}

void DRCClient::on_actionMediation_Process_triggered()
{
    if(_mediationProcessView && _mediationProcessView->getChangesPending())
    {
        if(_notesChanged)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to create new?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    setCentralWidget(new MediationProcessView());
                    _notesChanged = false;
                }
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to create new?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                setCentralWidget(new MediationProcessView());
            }
        }

    }
    else if(_mediationProcessView && _notesChanged)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            setCentralWidget(new MediationProcessView());
            _notesChanged = false;
        }
    }
    else
       setCentralWidget(new MediationProcessView());
}

void DRCClient::on_actionLogout_User_triggered()
{
    if(_mediationProcessView && _mediationProcessView->getChangesPending())
    {
        if(_notesChanged)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to leave?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    ui->toolBar->clear();
                    if(_browserDock && _browserDock->isVisible())
                        _browserDock->close();
                    SetMenusEnabled(false, false);
                    delete _mediationProcessView;
                    _mediationProcessView = nullptr;
                    setCentralWidget(new LoginForm());
                    _notesChanged = false;
                }
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to leave?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                ui->toolBar->clear();
                if(_browserDock && _browserDock->isVisible())
                    _browserDock->close();
                SetMenusEnabled(false, false);
                delete _mediationProcessView;
                _mediationProcessView = nullptr;
                setCentralWidget(new LoginForm());
                _notesChanged = false;
            }
        }

    }
    else if(_mediationProcessView && _notesChanged)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            ui->toolBar->clear();
            if(_browserDock && _browserDock->isVisible())
                _browserDock->close();
            SetMenusEnabled(false, false);
            delete _mediationProcessView;
            _mediationProcessView = nullptr;
            setCentralWidget(new LoginForm());
            _notesChanged = false;
        }
    }
    else
    {
        ui->toolBar->clear();
        if(_browserDock && _browserDock->isVisible())
            _browserDock->close();
        SetMenusEnabled(false, false);
        delete _mediationProcessView;
        _mediationProcessView = nullptr;
        setCentralWidget(new LoginForm());
    }
}

void DRCClient::on_mediationProcessSelected(MediationProcess* process)
{
    qDebug() << "DRC Client - on_mediationProcessSelected!";

    LoadMediationProcessView(process);
}

void DRCClient::LoadMediationProcessView(MediationProcess* process)
{
    if(_mediationProcessView)
    {
//        delete _mediationProcessView;
        _mediationProcessView = nullptr;
    }

    if(!_mediationProcessView)
        _mediationProcessView = new MediationProcessView(this, process);
    else _mediationProcessView->SetMediationProcess(process);
    setCentralWidget(_mediationProcessView);
}

void DRCClient::ShowNotesBrowser(MediatorArg arg)
{

    if(!arg.IsSuccessful())
    {

            closeNote = false;
    }
        ShowBrowser(MPBROWSER_NOTES);
}

void DRCClient::ShowSessionBrowser()
{
    ShowBrowser(MPBROWSER_SESSIONS);
}

void DRCClient::ShowMediationBrowser()
{
    ShowBrowser(MPBROWSER_MEDIATION);
}

void DRCClient::ShowBrowser(MPBrowserTypes browserType)
{
    // If the browser is open, and they selected the current type, close it.
    // Otherwise, show the type they selected.
    bool shouldDisplayTable = true;

    // If the browser dock already exists - check if we're closing it.
    if(_browserDock)
    {

        // Close the current window if the same browser is requested.
//        MPToolBox* toolbox = (MPToolBox*)_browserDock->widget();
        TabbedBrowsers* toolbox = (TabbedBrowsers*)_browserDock->widget();
        MPBrowserTypes curBrowser = toolbox->GetCurrentBrowserType();

        if(curBrowser == browserType)
        {

/*            if(_browserDock->isVisible())

            {

                _browserDock->close();
                removeDockWidget(_browserDock);
                disconnect(toolbox, SIGNAL(MPSelected(MediationProcess*)), this, SLOT(on_mediationProcessSelected(MediationProcess*)));
                _browserDock = nullptr;
                shouldDisplayTable = false;
            }
            else
*/            {
                _browserDock->show();
                shouldDisplayTable = false;
            }
        }
    }

    if(shouldDisplayTable)
    {
        // Create a new one if it doesn't exist.
        TabbedBrowsers* mpToolbox = nullptr;
        if(_browserDock)
        {
            mpToolbox = (TabbedBrowsers*)_browserDock->widget();
        }
        else
        {
            _browserDock = new QDockWidget("Browser Toolbox", this);
            mpToolbox = new TabbedBrowsers(_browserDock);
            connect(mpToolbox, SIGNAL(MPSelected(MediationProcess*)), this, SLOT(on_mediationProcessSelected(MediationProcess*)));
            _browserDock->setWidget(mpToolbox);
            addDockWidget(Qt::RightDockWidgetArea, _browserDock);
        }

        mpToolbox->ShowBrowser(browserType);

        // Update all the views, including the browsers
        if(_mediationProcessView)
            _mediationProcessView->PopulateView();
        else Mediator::Call(MKEY_DOCK_SET_NOTES); // sets notes to null and disables notes browser.

        if(!_browserDock->isVisible())
            _browserDock->show();
    }
}

void DRCClient::on_actionNew_2_triggered()
{
    _mediationProcessView = new MediationProcessView(this);
    _mediationProcessView->SetMediationProcess(new MediationProcess());
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
    setCentralWidget(_mediationProcessView);
}

void DRCClient::on_actionAdd_1_MP_sample_triggered()
{
    if(!_mediationProcessView)
        _mediationProcessView = new MediationProcessView(this);
    _mediationProcessView->SetMediationProcess(MediationProcess::SampleData());
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
    setCentralWidget(_mediationProcessView);
}

void DRCClient::on_actionAdd_to_vector_triggered()
{
    _mediationProcessVector->push_back(_mediationProcessView->GetMediationProcess());
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
}
// use to add mp via save event
void DRCClient::saveMPEvent(MediatorArg arg)
{
    MediationProcess* process = arg.getArg<MediationProcess*>();
    if(process)
    {
        _mediationProcessVector->push_back(process);
        Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
    }
}

void DRCClient::on_actionSave_to_file_triggered()
{
//    QFileDialog dialog(this);
//    dialog.setFileMode(QFileDialog::AnyFile);
//    dialog.setNameFilter(tr("*.mp"));
//    dialog.setViewMode(QFileDialog::Detail);

//    if(dialog.exec())
//        QStringList fileName = dialog.selectedFiles();
   if(_mediationProcessView)
   {
        QString Filter = "Mediation Processes (*.mp)";
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                    "",
                                    Filter,&Filter);

        _filemaker.setFileName(fileName);
        _filemaker.sendToFile(_mediationProcessVector);
   }
}

void DRCClient::on_actionLoad_from_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("*.mp"));
    if(!fileName.isEmpty())
    {
        _filemaker.getFromFile(fileName);
        _mediationProcessVector = _filemaker.getMedationProcessVector();
        if(_mediationProcessView)
        {
            //delete _mediationProcessView;
            _mediationProcessView = nullptr;
        }
        _mediationProcessView = new MediationProcessView(this);
        _mediationProcessView->SetMediationProcess(_mediationProcessVector->at(0));
        Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
        setCentralWidget(_mediationProcessView);
    }

}

void DRCClient::on_actionAdd_5_MP_samples_triggered()
{
    for(int i = 0; i < 5; i++)
    {
        _mediationProcessVector->push_back(MediationProcess::SampleData());
    }
    if(!_mediationProcessView)
        _mediationProcessView = new MediationProcessView(this);
    _mediationProcessView->SetMediationProcess(_mediationProcessVector->at(0));
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
    setCentralWidget(_mediationProcessView);
}

void DRCClient::send_mediation_vector()
{
    Mediator::Call(MKEY_DOCK_SET_MEDIATIONS,_mediationProcessVector);
}

void DRCClient::on_actionManage_Users_triggered()
{
    if(_mediationProcessView && _mediationProcessView->getChangesPending())
    {
        if(_mediationProcessView && _notesChanged)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to leave?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    setCentralWidget(new ManageUsers(this));
                    _notesChanged = false;
                }

            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to leave?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                setCentralWidget(new ManageUsers(this));
            }
        }
    }
    else if(_mediationProcessView && _notesChanged)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            ui->toolBar->clear();
            if(_browserDock && _browserDock->isVisible())
                _browserDock->close();
            SetMenusEnabled(false, false);
            delete _mediationProcessView;
            _mediationProcessView = nullptr;
            setCentralWidget(new LoginForm());
            _notesChanged = false;
        }
    }
    else
        setCentralWidget(new ManageUsers(this));
}

// Allow the admin to find a remote .db3 file to use. This file location will be stored as a file.
void DRCClient::on_actionConnect_to_Remote_DB_triggered()
{
    if(_mediationProcessView && _mediationProcessView->getChangesPending())
    {
        if(_notesChanged)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to leave?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    QString fileName = QFileDialog::getOpenFileName(this,
                                                                    "Open Remote Database", "", "Db Files (*.db3)");

                    if(fileName.length())
                    {
                        QFile file(DBPATH_FILE);
                        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                        {
                            file.write(fileName.toStdString().c_str());
                            file.close();
                            _db.LoadDatabase(fileName);
                            _notesChanged = false;
                        }
                    }
                }

            }
         }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to leave?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QString fileName = QFileDialog::getOpenFileName(this,
                                                                "Open Remote Database", "", "Db Files (*.db3)");

                if(fileName.length())
                {
                    QFile file(DBPATH_FILE);
                    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        file.write(fileName.toStdString().c_str());
                        file.close();
                        _db.LoadDatabase(fileName);
                    }
                }
            }
        }
    }
    else if(_mediationProcessView && _notesChanged)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            QString fileName = QFileDialog::getOpenFileName(this,
                "Open Remote Database", "", "Db Files (*.db3)");

            if(fileName.length())
            {
                QFile file(DBPATH_FILE);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    file.write(fileName.toStdString().c_str());
                    file.close();
                    _db.LoadDatabase(fileName);
                }
            }
            _notesChanged = false;
        }
    }
    else
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            "Open Remote Database", "", "Db Files (*.db3)");

        if(fileName.length())
        {
            QFile file(DBPATH_FILE);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                file.write(fileName.toStdString().c_str());
                file.close();
                _db.LoadDatabase(fileName);
            }
        }
    }
}

QString DRCClient::LoadDBPathFromFile()
{
    QString fileName = "";

    QFile file(DBPATH_FILE);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        fileName = in.readLine();
        file.close();
    }

    if(!fileName.length())
    {
        fileName = DB_DEFAULT_PATH;
    }
    return fileName;
}

void DRCClient::on_actionFindMediation_triggered()
{
    ShowMediationBrowser();
}

void DRCClient::ShowMainMenu()
{
    _mediationProcessView = nullptr;
    SetMenuBarEnabled();
    SetMenuHelpEnabled();
    ToolbarManager::Instance().Clear();
    setCentralWidget(new MainMenuForm(this));
}

void DRCClient::LoadEvaluationView()
{
    setCentralWidget(new MediationEvaluationView());

}

void DRCClient::ShowResWaReport()
{
    if(_mediationProcessView && _mediationProcessView->getChangesPending())
    {
        if(_notesChanged)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to leave?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    _mediationProcessView = nullptr;
                    setCentralWidget(new ResWaReportForm(this));
                    _notesChanged = false;
                }

            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to leave?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                _mediationProcessView = nullptr;
                setCentralWidget(new ResWaReportForm(this));
            }
        }
    }
    else if(_mediationProcessView && _notesChanged)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            _mediationProcessView = nullptr;
            setCentralWidget(new ResWaReportForm(this));
            _notesChanged = false;
        }
    }
    else
    {
        _mediationProcessView = nullptr;
        setCentralWidget(new ResWaReportForm(this));
    }
}

void DRCClient::ShowMonthlyReport()
{
//    SlideShowForm* slides = new SlideShowForm(this);
//    slides->SetSlideWidgets({new PersonDetailsForm, new MediationSessionForm, new NotesBrowser});
//    setCentralWidget(slides);
    if(_mediationProcessView && _mediationProcessView->getChangesPending())
    {
        if(_notesChanged)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to leave?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    setCentralWidget(new MonthlyReportForm(this));
                    _notesChanged = false;
                }

            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to leave?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                setCentralWidget(new MonthlyReportForm(this));
            }
        }
    }
    else if(_mediationProcessView && _notesChanged)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            setCentralWidget(new MonthlyReportForm(this));
            _notesChanged = false;
        }
    }
    else
       setCentralWidget(new MonthlyReportForm(this));
}

void DRCClient::on_actionMonthly_Report_triggered()
{
    ShowMonthlyReport();
}

void DRCClient::on_actionRes_Wa_Report_triggered()
{
    ShowResWaReport();
}

void DRCClient::on_actionSlots_Game_triggered()
{
    if(_mediationProcessView && _mediationProcessView->getChangesPending())
    {
        if(_notesChanged)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setText("Intake is not saved, are you sure you want to leave?");

                int selection = msgBox.exec();

                if(selection == QMessageBox::Yes)
                {
                    _mediationProcessView = nullptr;
                    setCentralWidget(new SlotsGame());
                    _notesChanged = false;
                }

            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setText("Intake is not saved, are you sure you want to leave?");

            int selection = msgBox.exec();

            if(selection == QMessageBox::Yes)
            {
                _mediationProcessView = nullptr;
                setCentralWidget(new SlotsGame());
            }
        }
    }
    else if(_mediationProcessView && _notesChanged)
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setText("Notes not saved, are you sure you want to continue without saving?");

        int selection = msgBox.exec();

        if(selection == QMessageBox::Yes)
        {
            _mediationProcessView = nullptr;
            setCentralWidget(new SlotsGame());
            _notesChanged = false;
        }
    }
    else
    {
        _mediationProcessView = nullptr;
        setCentralWidget(new SlotsGame());
    }
}

void DRCClient::Notes_Changed(MediatorArg args)
{
    auto seccess = args.getArg<bool*>();
    if(*seccess)
        _notesChanged = true;
    else
        _notesChanged = false;
}
