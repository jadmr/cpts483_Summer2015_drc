#ifndef DRCDB_H
#define DRCDB_H
#include "Mediator.h"

//#include "sqlite3.h"

#include "DBBaseObject.h"
#include "Crypto/SHA256_Crypto.h"
#include <string>
#include <vector>
#include <map>
#include <QtSql/QtSql>

class DRCDB
{
private:
    QSqlDatabase database;

    //Made it a vector in the event that multiple errors have occurred.
    //Though it shouldn't happen if we're doing accurate checks.
    QVector<QString> LastErrors;

    std::map<QString, QString> UserMap;

    bool DB_ERROR;

    bool ExecuteCommand(QString command_string, QSqlQuery &query_object);

    bool CreateTable(QString table_name, QVector<QString> column_data);

public:
    DRCDB();

    DRCDB(QString database_name);

    bool OpenDatabase(QString database_name);

    bool CloseDatabase();


    bool InsertObject(DBBaseObject* db_object);

    bool DuplicateInsert(const QString &duplicate_query);

    QVector<QString> SelectAllFields(QString table_name);

    bool ExtractError(const QSqlError &error_object);

    bool GetErrorOccurred();

    QVector<QString> GetLastErrors();


    // Incoming Events
    void PersistIntakeForm(MediatorArg arg) const;

    void PersistFruit(MediatorArg arg);

    void LoadIntake(MediatorArg arg) const;

    void LoadFruit(MediatorArg arg);

    void AuthenticateUser(MediatorArg arg);

};

#endif // DRCDB_H
