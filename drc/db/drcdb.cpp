#include "drcdb.h"
#include <QtSql/QtSql>
#include "Mediator.h"
#include "MediatorKeys.h"
#include "DRCModels.h"
#include "Fruit.h"    // temp.. not sure why it's having circular dependency.

#define db_driver "QSQLITE"

DRCDB::DRCDB() : DB_ERROR(false)
{
    OpenDatabase("../drc/drc_db.db3");

    //Name of the table we're creating.
    QString table_name = QString("Albertsons");

    //Name and Datatypes of all Table columns
    QVector<QString> column_container;
    column_container.push_back(QString("id integer primary key autoincrement null"));
    column_container.push_back(QString("fruit_name char(50) not null"));
    column_container.push_back(QString("time_stamp int not null"));

    CreateTable(table_name, column_container);

    // Populate our fake user list.  Delete this later!!
    UserMap["Admin"] = sha256("adminpassword", "");
    UserMap["Normal"] = sha256("normalpassword", "");
    UserMap[""] = sha256("", "");

    // Register to Listen for events.
    Mediator::Register(MKEY_GUI_AUTHENTICATE_USER, [this](MediatorArg arg){AuthenticateUser(arg);});

    Mediator::Register(MKEY_BL_VALIDATE_FRUITNAME_DONE, [this](MediatorArg arg){PersistFruit(arg);});
    Mediator::Register(MKEY_DB_PERSIST_FRUIT_NAME_DONE, [this](MediatorArg arg){LoadFruit(arg);});
//    Mediator::Register(MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE, [this](MediatorArg arg){LoadIntake(arg);});
//    Mediator::Register(MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE, [this](MediatorArg arg){PersistIntakeForm(arg);});
}

//========================================================================
//Constructor takes in a database_name, and opens it.
//------------------------------------------------------------------------
DRCDB::DRCDB(QString database_name) : DB_ERROR(false)
{
    this->OpenDatabase(database_name);
}
//========================================================================

//========================================================================
//Database authentication test code.  Not really touching the database,
//mostly emulating the appropriate Mediator calls we'll be needing.
//This will be the method called when authenticating a new user login.
//========================================================================
void DRCDB::AuthenticateUser(MediatorArg arg)
{
    User* user = nullptr;
    if(arg.IsSuccessful())
    {
        // Set arg.IsSuccessful() to false as default
        // Will only change to true when the user has been authenticated
        arg.SetSuccessful(false);

        user = arg.getArg<User*>();
        if(user)
        {
            // arg value type was a User
            if (UserMap.find(user->GetName()) != UserMap.end())
            {
                // Username found in UserMap
                if (user->GetPass() == UserMap[user->GetName()])
                {
                    // Set arg.IsSuccessful() to true
                    arg.SetSuccessful(true);
                    if (user->GetName() == "Admin")
                    {
                        user->SetType(USER_T_ADMIN);
                    }

                    // Reset arg value to the user.
                    // Assume the user object has been modified as needed
                    arg.SetArg(user);
                }
            }
        }
    }
    else
    {
        // Set the error label.
        //ui->statusLabel->setText(arg.ErrorMessage());
    }
    // Signal authentication has been completed
    Mediator::Call(MKEY_DB_AUTHENTICATE_USER_DONE, arg);
}
//========================================================================

//========================================================================
//It first sets the driver that our database will be using (in this case,
//"QSQLITE", which is the driver for sqlite3.  It'll then set the name of
//the database file to the QString that was passed to this method.

//After everything has been set on the database object, we attempt
//to open a database; we check if an error has occurred in the process of
//opening the database.  If an error had occurred, then we pass a
//QSqlError object to the GetError method.

//Return Values
//True:     Successfully Opened
//False:    Failed to Open
//------------------------------------------------------------------------
bool DRCDB::OpenDatabase(QString database_name)
{
    database = QSqlDatabase::addDatabase(db_driver);
    database.setDatabaseName(database_name);
    database.open();

    if(database.isOpenError())
        this->ExtractError(database.lastError());

    return database.isOpen();
}
//========================================================================



//========================================================================
//Method closes our database object, and returns the boolean indicating
//whether or not the database was successfully closed.

//True:     Closed
//False:    Still Open
//------------------------------------------------------------------------
bool DRCDB::CloseDatabase()
{
    database.close();
    return !database.isOpen();
}
//========================================================================



//========================================================================
//Consolidates a command_string with all the individual elements from the
//QVector that will make up the columns of this new table.

//Lastly we use the ExecuteCommand method of our database class to generate
//the tables, and returns a boolean indicating whether or not it was successful.
//True:     Command Executed
//False:    Command Failed to Execute
//------------------------------------------------------------------------
bool DRCDB::CreateTable(QString table_name, QVector<QString> column_data)
{
    QString command_string = QString("create table %1 ").arg(table_name);

    command_string += "(";

    for (auto index = column_data.begin() ; index < column_data.end() ; ++index)
    {
        if (index != column_data.begin())
            command_string += ", ";

        command_string += *index;
    }

    command_string += ")";

    QSqlQuery query_object(database);
    return this->ExecuteCommand(command_string, query_object);
}
//========================================================================



//========================================================================
//Takes a generic Database object, and parses a valid command_string.
//This string is then sent to our ExecuteCommand method of our database
//class to insert the values of the object.
//------------------------------------------------------------------------
bool DRCDB::InsertObject(DBBaseObject* db_object)
{
    bool insert_success = false;

    if (!this->DuplicateInsert(db_object->DuplicateQuery()))
    {
        QString command_string = QString("insert into %1 values ( %2 , %3 )")
                .arg(db_object->table())
                .arg("null")
                .arg(db_object->Parse());

        QSqlQuery query_object(database);
        insert_success = this->ExecuteCommand(command_string, query_object);
    }

    return insert_success;
}
//========================================================================



//========================================================================
//A simple query to determine whether or not a similar name already exists
//inside the database.

//Note: It seems QSqlQuery.size() is not compatible with SQLITE3, which
//      resulted in using QSqlQuery.next() instead.

//Note: Unfortunately we can't use ExecuteCommand method to prevent
//      duplicate code due to the fact that we still need the
//      query_object that goes out of scope.
//------------------------------------------------------------------------
bool DRCDB::DuplicateInsert(const QString &duplicate_query)
{
    bool duplicate_exists = false;

    QSqlQuery query_object(database);
    if(this->ExecuteCommand(duplicate_query, query_object))
    {
        if (query_object.next())
        {
            duplicate_exists = true;
            DB_ERROR = true;
            LastErrors.push_back(QString("Duplicate Insert Was Attempted: %1.")
                                 .arg(duplicate_query));
        }
    }

    return duplicate_exists;
}
//========================================================================



//========================================================================
//Query object can be implicitly initialized without passing
//the QSQLDatabase object to the constructor.  However, it is
//slightly more obvious as to where it's getting its information.

//Prepare checks the potential SQL command for validity.  While it seems
//tedious, it apparently is more efficient than letting an erroneous
//command be executed directly.

//------------------------------------------------------------------------
bool DRCDB::ExecuteCommand(QString command_string, QSqlQuery &query_object)
{
    if(!query_object.prepare(command_string))
        this->ExtractError(query_object.lastError());

    return query_object.exec();
}
//========================================================================



//========================================================================
//A simple query that returns all values currently contained within the
//table indicated.

//Unlike previous database methods, this method is unable to use the
//ExecuteCommand method due to the fact that it needs to return an object
//as opposed to a simple boolean.  In this case, an empty object represents
//a failed attempt to return anything from the database.
//QVector.count > 0:        Success
//QVector.count == 0:       Failure
//------------------------------------------------------------------------
QVector<QString> DRCDB::SelectAllFields(QString table_name)
{
    QVector<QString> return_vec;

    QString command_string = QString("select * from %1")
            .arg(table_name);

    QSqlQuery query_object(database);
    this->ExecuteCommand(command_string, query_object);

    while(query_object.next())
    {
        QString time(query_object.value(0).toString());
        QString name(query_object.value(1).toString());
        QString id(query_object.value(2).toString());
        return_vec.push_back(time);
        return_vec.push_back(name);
        return_vec.push_back(id);
    }

    return return_vec;
}
//========================================================================



//========================================================================
//Takes a QSqlError object, and checks to make sure an error has been set
//in the error_object before the error string is appended to the LastError
//vector.

//Return Values
//True:     Error Occurred
//False:    No Error Occurred / Detected
//------------------------------------------------------------------------
bool DRCDB::ExtractError(const QSqlError &error_object)
{
    DB_ERROR = error_object.isValid();

    if (DB_ERROR)
        LastErrors.push_back(error_object.text());

    return DB_ERROR;
}
//========================================================================



//========================================================================
//Return Values
//True:     Error has occurred
//False:    Error has not occurred
//------------------------------------------------------------------------
bool DRCDB::GetErrorOccurred()
{
    return DB_ERROR;
}
//========================================================================



//========================================================================
//Returns a vector containing all the errors that has occurred since its
//last call.

//Note:     It's sloppy, but currently the method sets the DB_ERROR
//          back to false whenever this method is called.

//          If DB_ERROR was set to true due to a SqlQueryError, the
//          problem was likely resolved when the query_object went out
//          of scope.

//          If DB_ERROR was set to true due to open database failing,
//          then the problem is more permenant.
//------------------------------------------------------------------------
QVector<QString> DRCDB::GetLastErrors()
{
    DB_ERROR = !database.isOpenError();

    QVector<QString> retVec = LastErrors;
    LastErrors.clear();

    return retVec;
}
//========================================================================

//void DRCDB::PersistIntakeForm(MediatorArg arg) const
//{
//    bool success = arg.IsSuccessful();
//    QString errorMessage = arg.ErrorMessage();

//    Intake* intake = nullptr;       // Unpackaged argument
//    if (success)
//    {
//        intake = arg.getArg<Intake*>();

//        // SUCCESS!! INSERT CODE HERE
//    }


//    qDebug() << "DB -> PersistIntakeForm Complete";
//    Mediator::Call(MKEY_DB_PERSIST_INTAKE_FORM_DONE, intake, success, errorMessage);
//}

void DRCDB::PersistFruit(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    QString errorMessage = arg.ErrorMessage();

    Fruit* fruit = nullptr;       // Unpackaged argument
    if (success)
    {
        fruit = arg.getArg<Fruit*>();

        InsertObject(fruit);
    }

    qDebug() << "DB -> PersistFruit Complete";
    Mediator::Call(MKEY_DB_PERSIST_FRUIT_NAME_DONE, fruit, success, errorMessage);
}

void DRCDB::LoadFruit(MediatorArg arg)
{
    QVector<QString> results = SelectAllFields(QString("Albertsons"));
    qDebug() << "Data stored in database; name then timestamp\n";
    for(unsigned int i = 0; i < results.size(); i++)
    {
        qDebug() << results.at(i) << endl;
    }
    qDebug() << "DB -> LoadFruit Complete";
}

//void DRCDB::LoadIntake(MediatorArg arg) const
//{
//    bool success = arg.IsSuccessful();
//    QString errorMessage = arg.ErrorMessage();

//    Intake* intake = nullptr;       // Unpackaged argument
//    if (success)
//    {
//        // Returning a test object... This should be deleted!!!
//        intake = new Intake();
//        intake->addClaimant(Person("CLAIMENT DB TEST"));
//        intake->addRespondents(Person("Respondent1"));
//        intake->addRespondents(Person("Respondent2"));
//        intake->addRespondents(Person("Respondent3"));

//        // SUCCESS!! INSERT CODE HERE
//    }

//    qDebug() << "DB -> PersistIntakeForm Complete";
//    Mediator::Call(MKEY_DB_LOAD_INTAKE_FORM_DONE, intake, success, errorMessage);
//}
