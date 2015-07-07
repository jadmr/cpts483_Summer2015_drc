#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <direct.h>
#include <QtSql/QtSql>
#include <fstream>
#include "DRCClient.h"
#include <QApplication>

//#include "olddatabase.cpp"
//#include "newdatabase.cpp"

void makeFolders();
void getOutDatedDatabase(QSqlDatabase& database);
void makeUpDatedDatabase(QSqlDatabase& database);
void CreateConvertedDatabase();
bool openDatabase(QString database_name, QSqlDatabase &database);
bool databaseExists(char *filename);
MediationProcessVector* organizeMediationProcessVector(MediationProcessVector* unorganized);

int main(int argc, char *argv[])
{
    //Start the core application
    QCoreApplication a(argc, argv);

    //Make folders
    //makeFolders();

    //Print out information about the program
    qDebug()<< "--------------Database Converter--------------"<< endl << endl << "This will convert an outdated database file into an updated format. "
               "Place the outdated database in the folder named 'Outdated' in the executable directory."
               "The updated database will be in the folder named 'Updated' in the executable directory."
               << endl << endl << "NOTE: The Outdated Database needs to be named 'drc_db.db3'" << endl;

    //system("PAUSE");
    system("CLS");

    //Get the databases
    DRCDB db;

    //Get the OLD database
    qDebug() << "Fetching Outdated Database... ";
    db.LoadDatabase(QString("OutDated\\drc_db.db3"));
    qDebug() << "DONE" << endl;

    MediationProcessVector* oldMediations = db.getMediationProcesses();

    oldMediations = organizeMediationProcessVector(oldMediations);

    /*system("pause");
    qDebug() << "The vector is " << oldMediations->size() << " elements long.";
    for (int i =0; i < oldMediations->size(); i++)
    {
        MediationProcess* temp = oldMediations->at(i);
        qDebug() << temp->GetId() << ", ";
    }
    system("pause");*/


    db.CloseDatabase();

    qDebug() << "Making New Database... ";
    db.LoadDatabase2(QString("UpDated\\drc_db.db3"));
    qDebug() << "DONE" << endl;

    db.InsertMediationVector(oldMediations);


    //Running Test
    db.LoadDatabase(QString("UpDated\\drc_db.db3"));
    MediationProcessVector* newMediations = db.getMediationProcesses();
    newMediations = organizeMediationProcessVector(newMediations);

    qDebug() <<"Test: ";

    system("pause");
    for (int i=0; i<newMediations->size();i++)
    {
        MediationProcess* tempOld = oldMediations->at(i);
        MediationProcess* tempNew = newMediations->at(i);
        bool result = tempOld == tempNew;
        qDebug() << result;
    }
    system("pause");

    exit(1);
    return a.exec();
}

void makeFolders()
{
    mkdir("Outdated");
    mkdir("Updated");
}

//void getOutDatedDatabase(QSqlDatabase& database)
//{
//    qDebug() << "Fetching Outdated Database..." << endl;

//    //Filename - We need to different datatypes for the same file becuse you can't static cast them
//    QString path = "Outdated/drc_db.db3";
//    char * pathChar = "Outdated/drc_db.db3";

//    //Make sure that the database exists
//    if (databaseExists(pathChar))
//    {
//        qDebug() << "Database found." << endl;
//    }
//    else
//    {
//        qDebug() << "ERROR: Database not found!!!!" << endl;
//        exit(1);
//    }

//    //Open the database
//    if (openDatabase(path, database))
//    {
//        qDebug() << "Database Opened Successfully." << endl;
//    }
//    else
//    {
//        qDebug() << "ERROR: Database not opened correctly!!!!" << endl;
//        exit(1);
//    }

//    qDebug() << "DONE!" << endl;
//}

//void makeUpDatedDatabase(QSqlDatabase& database)
//{
//    qDebug() << "Making Updated Database..." << endl;

//    //Filename - We need to different datatypes for the same file becuse you can't static cast them
//    QString path = "Updated/drc_db.db3";
//    char * pathChar = "Updated/drc_db.db3";

//    //Make sure that the database exists
//    if (databaseExists(pathChar))
//    {
//        qDebug() << "ERROR: Database found in Updated folder! Please Remove!" << endl;
//        exit(1);
//    }
//    else
//    {
//        qDebug() << "Database folder found." << endl;
//    }

//    //Open the database
//    if (openDatabase(path, database))
//    {
//        qDebug() << "Database Opened Successfully." << endl;
//    }
//    else
//    {
//        qDebug() << "ERROR: Database not opened correctly!!!!" << endl;
//        exit(1);
//    }

//    qDebug() << "DONE!" << endl;
//}

void getOutDatedDatabase()
{
    qDebug() <<"Fetching Outdated Database..." << endl;

    //Filename - We need to different datatypes for the same file becuse you can't static cast them
    QString path = "Outdated/drc_db.db3";
    char * pathChar = "Outdated/drc_db.db3";

    //Make sure that the database exists
    if (databaseExists(pathChar))
    {
        qDebug() << "Database found." << endl;
    }
    else
    {
        qDebug() << "ERROR: Database not found!!!!" << endl;
        exit(1);
    }

    //Open the database
    QSqlDatabase database;
    if (openDatabase(path, database))
    {
        qDebug() << "Database Opened Successfully." << endl;
    }
    else
    {
        qDebug() << "ERROR: Database not opened correctly!!!!" << endl;
        exit(1);
    }

    qDebug() << "DONE!" << endl;
}

bool openDatabase(QString database_name, QSqlDatabase &database)
{
    database = QSqlDatabase::addDatabase("QSQLITE", QString("Current_Connection"));
    database.setDatabaseName(database_name);
    database.setConnectOptions(QString("foreign_keys = ON"));
    database.open();

    return database.isOpen();
}

bool databaseExists(char *filename)
{
  std::ifstream file(filename);
  return file;
}

void CreateConvertedDatabase()
{
    qDebug() << "Converting Outdated Database..." << endl;

    //Get the list of items

    qDebug() <<"Items found." << endl;

    qDebug() << "DONE!" << endl;
}


/*#include "DRCClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DRCClient w;
    w.setWindowTitle("Mediation Intake Management Environment");
    w.setWindowIcon(QIcon(":image/DRClogoFromJpg.ico"));
    w.show();

    return a.exec();
}

*/
MediationProcessVector* organizeMediationProcessVector(MediationProcessVector* unorganized)
{
    //Get the size of the unorganized vecotr
    int vectorLength = unorganized->size();

    //Make a new organized vector
    MediationProcessVector* organized = new MediationProcessVector;

    //Bubble loop
    for (int i=0;i<vectorLength;i++)
    {
        for (int ii=0;ii<vectorLength;ii++)
        {
            MediationProcess* temp = unorganized->at(ii);
            if (temp->GetId() == i + 1)
            {
                organized->push_back(temp);
                break;
            }
        }
    }

    if (organized->size() == vectorLength)
    {
        return organized;
    }
    else
    {
        return NULL;
    }
}
