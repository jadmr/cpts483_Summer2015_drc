#include "manageusers.h"
#include "ui_manageusers.h"

// Temp
#include <iostream>

ManageUsers::ManageUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageUsers)
{
    ui->setupUi(this);

    _admin = false;

    _selectedUser = nullptr;

    // Make it so the passwords entered can't be seen.
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->reenterpasswordLineEdit->setEchoMode(QLineEdit::Password);

    // Mediator method registers
    Mediator::Register(MKEY_DB_RETURN_ALL_USER, [this](MediatorArg arg){GetAllUsers(arg);});
    Mediator::Call(MKEY_DB_GET_ALL_USER);

    ConfigureUserTableView();
    PopulateUserTableView();
}

ManageUsers::~ManageUsers()
{
    delete ui;
}

void ManageUsers::ConfigureUserTableView()
{

    ui->usertableWidget->setColumnCount(2);
    ui->usertableWidget->setRowCount(_userVector->count());
    ui->usertableWidget->setColumnWidth(0, ui->usertableWidget->width()/2);
    ui->usertableWidget->setColumnWidth(1, ui->usertableWidget->width()/2);

    QStringList Header;
    Header << "Username" << "Admin Status";
    ui->usertableWidget->setHorizontalHeaderLabels(Header);
    ui->usertableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    ui->usertableWidget->verticalHeader()->setVisible(false);
    ui->usertableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->usertableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->usertableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->usertableWidget->setShowGrid(true);
    ui->usertableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
}

void ManageUsers::PopulateUserTableView()
{
    for (int row = 0; row < _userVector->count(); row++)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem(_userVector->at(row)->GetName());
        item1->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *item2 = new QTableWidgetItem(_userVector->at(row)->GetType() == USER_T_ADMIN ? "Yes" : "No");
        item2->setTextAlignment(Qt::AlignCenter);

        ui->usertableWidget->setItem(row, 0, item1);
        ui->usertableWidget->setItem(row, 1, item2);
    }
}

void ManageUsers::GetAllUsers(MediatorArg arg)
{
    if (arg.IsSuccessful())
    {
        _userVector = arg.getArg<QVector<User*>*>();
    }
}

void ManageUsers::on_AddUserButton_clicked()
{
    if (_passwordMatch && _username != "" && _password != "")
    {
        User *newUser = new User();
        newUser->SetName(_username);
        newUser->SetPassword(_password);
        newUser->SetType((_admin == true ? USER_T_ADMIN : USER_T_NORMAL));
        _selectedUser = newUser;

        MediatorArg arg;
        arg.SetArg(newUser);
        Mediator::Call(MKEY_DB_ADD_NEW_USER, arg);
    }

    ConfigureUserTableView();
    PopulateUserTableView();
}

void ManageUsers::on_DeleteUserButton_clicked()
{
    if (_selectedUser != nullptr)
    {
        MediatorArg arg;
        arg.SetArg(_selectedUser);
        Mediator::Call(MKEY_DB_REMOVE_USER, arg);
    }

    ConfigureUserTableView();
    PopulateUserTableView();
}

void ManageUsers::on_usernameLineEdit_editingFinished()
{
    _username = ui->usernameLineEdit->text();
}

void ManageUsers::on_passwordLineEdit_editingFinished()
{
    _password = ui->passwordLineEdit->text();
}

void ManageUsers::on_reenterpasswordLineEdit_editingFinished()
{
    _reenteredpassword = ui->reenterpasswordLineEdit->text();
}

void ManageUsers::on_reenterpasswordLineEdit_textChanged(const QString &arg1)
{
    if (arg1 != _password)
    {
        ui->MatchingPasswordLabel->setStyleSheet("QLabel {color : red}");
        ui->MatchingPasswordLabel->setText("No Match!!");

        _passwordMatch = false;
    }
    else
    {
        ui->MatchingPasswordLabel->setStyleSheet("QLabel {color : green}");
        ui->MatchingPasswordLabel->setText("Match!");

        _passwordMatch = true;
    }
}

void ManageUsers::on_IsAdminBox_toggled(bool checked)
{
    _admin = checked;
}
