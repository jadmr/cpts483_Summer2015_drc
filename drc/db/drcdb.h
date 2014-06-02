#ifndef DRCDB_H
#define DRCDB_H
#include "drc_shared/mediator/Mediator.h"

#include "sqlite3.h"
#include <string>
#include <vector>
#include <QtSql/QtSql>

class DRCDB
{
private:
    QSqlDatabase database;
	bool DB_ERROR;

public:

    DRCDB();
	
	void OpenDatabase(std::string database_name);
	
	void InsertField(std::string fruit_name, std::string time_stamp);

	std::vector<std::string> SelectAllField();

	bool isError();

	std::string errorMessage();


    // Incoming Events
    void PersistIntakeForm(MediatorArg arg) const;

    void PersistFruit(MediatorArg arg) const;

    void LoadIntake(MediatorArg arg) const;

};

#endif // DRCDB_H
