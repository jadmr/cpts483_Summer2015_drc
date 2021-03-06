#include "persondetailsform.h"
#include "ui_persondetailsform.h"
#include "Person.h"
#include <QDebug>

PersonDetailsForm::PersonDetailsForm(QWidget *parent, Person* person, bool bPopup)
    : QWidget(parent)
    , ui(new Ui::PersonDetailsForm)
    , _person(person ? person : new Person())
    , _shouldCleanPersonPointer(person == nullptr)
    , _bPopup(bPopup)
{
    ui->setupUi(this);
    _loading = true;
    // Setup Validations
    ui->zipLineEdit->setValidator(new QIntValidator(ui->zipLineEdit));
    //ui->adultsInHomeSpinBox->setValidator(new QIntValidator(ui->adultsInHomeSpinBox));
    //CountyIds quickCountyBugFix = _person->getCounty();
    configureComboBoxes();
    //_person->setCounty(quickCountyBugFix);
    // If a valid person object was passed, display it and don't go into edit mode.
    if(person)
        UpdateLabels();
    else
        SetEditMode(true);      // Blank record, start in edit mode.
    ui->groupBox->setStyleSheet("QGroupBox#groupBox {border: 2px solid gray; border-radius: 5px; margin-top: 10px;}");
//    ui->emailFrame->setStyleSheet("QFrame {border: 2px solid gray; border-radius: 5px; margin-top: 1.3px;}");
    ui->miscFrame->setStyleSheet("QFrame#miscFrame {border: 2px solid gray; border-radius: 5px; margin-top: 8px;}");
    ui->addressGroupBox->setStyleSheet("QGroupBox#addressGroupBox {border: 2px solid gray; border-radius: 5px; margin-top: 10px;}");
    _loading = false;
}

PersonDetailsForm::~PersonDetailsForm()
{
    delete ui;
    cleanPerson();
}

void PersonDetailsForm::keyPressEvent(QKeyEvent *pe)
{
    if(pe->key() == Qt::Key_Return) on_saveButton_clicked();
}

void PersonDetailsForm::configureComboBoxes()
{
    for(int i = 0; i < 7; i++)
        ui->countyComboBox->addItem(StringForCountyIds((CountyIds)i));
}

void PersonDetailsForm::UpdateLabels()
{
    _loading = true;
    ui->firstLineEdit->setText((_person->getFirstName()));
    ui->middleLineEdit->setText((_person->getMiddleName()));
    ui->lastLineEdit->setText((_person->getLastName()));
    ui->streetLineEdit->setText((_person->getStreet()));
    ui->unitLineEdit->setText((_person->getUnit()));
    ui->cityLineEdit->setText((_person->getCity()));
    ui->stateLineEdit->setText((_person->getState()));
    ui->countyComboBox->setCurrentIndex((int)(_person->getCounty()));
    ui->zipLineEdit->setText((_person->getZip()));
    ui->emailLineEdit->setText((_person->getEmail()));
    ui->primaryLineEdit->setText((_person->getPrimaryPhone()));
    ui->primaryExtLineEdit->setText((_person->getPrimaryPhoneExt()));
    ui->secondaryLineEdit->setText((_person->getSecondaryPhone()));
    ui->secondaryExtLineEdit->setText((_person->getSecondaryPhoneExt()));
//    ui->mobileLineEdit->setText((_person->getMobilePhone()));
//    ui->mobileExtLineEdit->setText((_person->getMobilePhoneExt()));
    ui->adultsInHomeSpinBox->setValue(_person->getNumberInHousehold());
    ui->childrenInHomeSpinBox->setValue(_person->getNumberChildrenInHousehold());
    ui->attorneyLineEdit->setText((_person->getAttorney()));
    ui->attorneyEmailLineEdit->setText(_person->getAttorneyEmail());
    ui->attorneyPhoneLineEdit->setText(_person->getAttorneyPhone());
    ui->assistantNameLineEdit->setText(_person->getAssistantName());
    ui->assistantEmailLineEdit->setText(_person->getAssistantEmail());
    ui->assistantPhoneLineEdit->setText(_person->getAssistantPhone());
    _loading = false;
//    SetEditMode(false);
}

void PersonDetailsForm::SetWidgetInvalid(QWidget *widget)
{
    QPalette palette;
    palette.setColor( widget->foregroundRole(), Qt::red );
    widget->setPalette(palette);
}

void PersonDetailsForm::SetWidgetValid(QWidget *widget)
{
    QPalette palette;
    palette.setColor( widget->foregroundRole(), Qt::black );
    widget->setPalette(palette);
}

bool PersonDetailsForm::ValidateForm()
{
    // Check every field and return true if they all pass, else false.

    if(
        ProcessPhoneNumber(ui->primaryLineEdit->text(), ui->primaryLineEdit)
        &&
        ProcessPhoneNumber(ui->secondaryLineEdit->text(), ui->secondaryLineEdit)
        &&
//        ProcessPhoneNumber(ui->mobileLineEdit->text(), ui->mobileLineEdit)
//        &&
        ProcessEmail(ui->emailLineEdit->text(), ui->emailLineEdit)
    )
    {
        return true;
    }

    return false;
}


bool PersonDetailsForm::ProcessEmail(const QString& string, QLineEdit* widget)
{
    // email validation - <something>@<something>.<two to three letters>
    QRegExp rx("(^.*@.*[.][a-z]{2,3})");
    QRegExpValidator v(rx, 0);
    QString s = string;
    if(!rx.exactMatch(s))
    {
        SetWidgetInvalid(widget);
        return false;
    } else {
        SetWidgetValid(widget);
        return true;
    }
}

bool PersonDetailsForm::ProcessPhoneNumber(const QString& string, QLineEdit* widget)
{
    if(string.length() == 0) return true;

    QString s = string;
    QString last = _phoneMap[widget];   // previously stored value.

    // Only auto complete if delete was not pushed and we have a
    QRegExp rx;
    if(last.length() != string.length() + 1)
    {
        // Auto complete first dash
        rx.setPattern("(^[0-9]{3})");
        if(rx.exactMatch(s))
            s.append("-");

        // Auto complete second dash
        rx.setPattern("^[0-9]{3}-[0-9]{3}");
        if(rx.exactMatch(s))
            s.append("-");
    }

    // Save the new string to the map for later comparisons
    _phoneMap[widget] = s;

    // phone validation - xxx-xxx-xxxx
    rx.setPattern("^[0-9]{3}-[0-9]{3}-[0-9]{4}");
    widget->setText(s);
    if(!rx.exactMatch(s))
    {
        //SetWidgetInvalid(widget);
        return false;
    } else {
        SetWidgetValid(widget);
        return true;
    }
}

void PersonDetailsForm::on_saveButton_clicked()
{
    SetEditMode(false);

    _person->setFirstName(ui->firstLineEdit->text());
    _person->setMiddleName(ui->middleLineEdit->text());
    _person->setLastName(ui->lastLineEdit->text());
    _person->setStreet(ui->streetLineEdit->text());
    _person->setUnit(ui->unitLineEdit->text());
    _person->setCity(ui->cityLineEdit->text());
    _person->setState(ui->stateLineEdit->text());
    _person->setCounty((CountyIds)ui->countyComboBox->currentIndex());
    _person->setZip(ui->zipLineEdit->text());
    _person->setEmail(ui->emailLineEdit->text());
    _person->setPrimaryPhone(ui->primaryLineEdit->text());
    _person->setPrimaryPhoneExt(ui->secondaryExtLineEdit->text());
    _person->setSecondaryPhone(ui->secondaryLineEdit->text());
    _person->setSecondaryPhoneExt(ui->primaryExtLineEdit->text());
    _person->setNumberInHousehold(ui->adultsInHomeSpinBox->value());
    _person->setAttorney(ui->attorneyLineEdit->text());


    //emit PersonSaved(_person);
    //emit SaveSignaled();
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    if(_bPopup)
    {
        this->close();
    }
}

void PersonDetailsForm::on_editButton_clicked()
{
    SetEditMode(true);
}

void PersonDetailsForm::on_deleteButton_clicked()
{
    emit PersonDeleted(_person);

    SetEditMode(true);
    _person = new Person();
    UpdateLabels();

    if(_bPopup)
    {
        this->close();
    }
}

void PersonDetailsForm::SetEditMode(bool editModeOn)
{
    editModeOn = true;
    ui->firstLineEdit->setEnabled(editModeOn);
    ui->middleLineEdit->setEnabled(editModeOn);
    ui->lastLineEdit->setEnabled(editModeOn);
    ui->streetLineEdit->setEnabled(editModeOn);
    ui->unitLineEdit->setEnabled(editModeOn);
    ui->cityLineEdit->setEnabled(editModeOn);
    ui->stateLineEdit->setEnabled(editModeOn);
    ui->countyComboBox->setEnabled(editModeOn);
    ui->zipLineEdit->setEnabled(editModeOn);
    ui->emailLineEdit->setEnabled(editModeOn);
    ui->primaryLineEdit->setEnabled(editModeOn);
    ui->primaryExtLineEdit->setEnabled(editModeOn);
    ui->secondaryLineEdit->setEnabled(editModeOn);
    ui->secondaryExtLineEdit->setEnabled(editModeOn);
    ui->adultsInHomeSpinBox->setEnabled(editModeOn);
    ui->attorneyLineEdit->setEnabled(editModeOn);

//    ui->saveButton->setEnabled(editModeOn);
//    ui->editButton->setEnabled(!editModeOn);

    _editModeOn = editModeOn;

}

void PersonDetailsForm::cleanPerson()
{
//    if(_shouldCleanPersonPointer)
//        delete _person;
//    _shouldCleanPersonPointer = false;
}

void PersonDetailsForm::on_firstLineEdit_returnPressed()
{

}

void PersonDetailsForm::SetPerson(Person *p)
{
    cleanPerson();
    _person = p;
    UpdateLabels();
}


void PersonDetailsForm::ShowButtons(bool showButtons)
{
    if(showButtons)
    {
//        ui->buttonContainer->setVisible(true);
        SetEditMode(false);
    }
    else
    {
//        ui->buttonContainer->setVisible(false);
        SetEditMode(true);
    }
}

void PersonDetailsForm::on_middleLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setMiddleName(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}


void PersonDetailsForm::on_streetLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setStreet(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_unitLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setUnit(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_cityLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setCity(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_zipLineEdit_textEdited(const QString &arg1)
{
    _person->setZip(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_stateLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setState(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_attorneyLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setAttorney(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_emailLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setEmail(arg1);
    ProcessEmail(arg1, ui->emailLineEdit);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_primaryLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setPrimaryPhone(arg1);
    ProcessPhoneNumber(arg1, ui->primaryLineEdit);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_primaryExtLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setPrimaryPhoneExt(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_secondaryLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setSecondaryPhone(ui->secondaryLineEdit->text());
    ProcessPhoneNumber(arg1, ui->secondaryLineEdit);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_secondaryExtLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setSecondaryPhoneExt(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_lastLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setLastName(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_firstLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setFirstName(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_adultsInHomeSpinBox_editingFinished()
{
    if(_loading) return;
    _person->setNumberInHousehold(ui->adultsInHomeSpinBox->value());
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_assistantLineEdit_editingFinished()
{
//    _person->setAssistantName(ui->assistantNameLineEdit->text());
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_countyComboBox_currentIndexChanged(int index)
{
    if(_loading) return;
//    int savedCounty = (int)_person->getCounty();
    if(index != (int)_person->getCounty())
    {
        _person->setCounty((CountyIds)index);
        Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    }
}

void PersonDetailsForm::on_childrenInHomeSpinBox_editingFinished()
{
    if(_loading) return;
    _person->setNumberChildrenInHousehold(ui->childrenInHomeSpinBox->value());
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_attorneyPhoneLineEdit_editingFinished()
{
//    _person->setAttorneyPhone(ui->attorneyPhoneLineEdit->text());
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_attorneyEmailLineEdit_editingFinished()
{
//    _person->SetAttorneyEmail(ui->attorneyEmailLineEdit->text());
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_assistantPhoneLineEdit_editingFinished()
{
//    _person->setAssistantPhone(ui->assistantPhoneLineEdit->text());
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_assistantEmailLineEdit_editingFinished()
{
//    _person->setAssistantEmail(ui->assistantEmailLineEdit->text());
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_assistantNameLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setAssistantName(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_attorneyPhoneLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setAttorneyPhone(arg1);
    ProcessPhoneNumber(arg1,ui->attorneyPhoneLineEdit);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_attorneyEmailLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->SetAttorneyEmail(arg1);
    ProcessEmail(arg1, ui->attorneyEmailLineEdit);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_assistantPhoneLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setAssistantPhone(arg1);
    ProcessPhoneNumber(arg1, ui->assistantPhoneLineEdit);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_assistantEmailLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    _person->setAssistantEmail(arg1);
    ProcessEmail(arg1, ui->assistantEmailLineEdit);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void PersonDetailsForm::on_notesPushButton_clicked()
{
    MediatorArg *a = new MediatorArg();
    a->SetSuccessful(false);
    Mediator::Call(MKEY_GUI_SHOW_NOTES_BROWSER, a);
    UpdateLabels();
}
