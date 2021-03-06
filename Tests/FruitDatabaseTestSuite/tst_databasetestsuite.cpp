#include <QString>
#include <QtTest>
#include <QDebug>
#include <QFile>
#include <QVector>

#include "drcdb.h"
#include "Fruit.h"
#include "Basket.h"

//Tests:
//
//Open Database
//1.  Ensure database file is named the name we named it.
//2.  To check database name, database must be opened first.
//3.  Is the database using the driver we needed?
//
//Create Table  (In truth, schema is largely pre-determined; but might as well)
//1.  Was the Table successfully created?
//2.  Does the Schema of the table match with what we intended?
//3.  Does the name of the Table already exist?
//3a.   Seems redundant, but it maybe more efficient to find a table name
//      rather than to have the SQL DBMS discover it on compiling the command.

class DatabaseTestSuite : public QObject
{
    Q_OBJECT

public:
    DatabaseTestSuite();

private:
    DRCDB _db;

    QString database_name;
    QString database_driver;
    QString table_name;
    QVector<QString> column_container;
    QVector<QString> empty_container;


private Q_SLOTS:
    void OpenDatabase();
    void CreateTable();
    void CreateDuplicateTable();
    void InsertObject();
    void SelectName();

private slots:
    void cleanupTestCase()
    {
        QCOMPARE(_db.CloseDatabase(), true);

        //For the sake of this Test Suite, we delete database after every run.
        //Comment out if undesirable; IE, looking inside file directly.
        QCOMPARE(QFile::remove(database_name), true);
    }
};

//  Change information to accomodate new circumstances.
//======================================================
DatabaseTestSuite::DatabaseTestSuite()
{
    //Name of the database we're using / creating.
    database_name = QString("database_test_name.db");

    //Name of the driver we're using.
    database_driver = QString("QSQLITE");

    //Name of the table we're creating.
    table_name = QString("Albertsons");

    //Name and Datatypes of all Table columns
    column_container.push_back(QString("id integer primary key autoincrement null"));
    column_container.push_back(QString("fruit_name char(50) not null"));
    column_container.push_back(QString("time_stamp int not null"));

}
//=======================================================

void DatabaseTestSuite::OpenDatabase()
{
    //Did the database open?
    QCOMPARE(_db.OpenDatabase(database_name), true);
}

void DatabaseTestSuite::CreateTable()
{
    //Create table with name and column data.
    QCOMPARE(_db.CreateTable(table_name, column_container), true);
    table_name = "Basket";
    column_container.clear();
    column_container.push_back(QString("id integer primary key autoincrement null"));
    column_container.push_back(QString("basket_name char(50) not null"));
    _db.CreateTable(table_name, column_container);
    table_name = "FruitBasket";
    column_container.clear();
    column_container.push_back(QString("id integer primary key autoincrement null"));
    column_container.push_back(QString("basket_id int not null"));
    column_container.push_back(QString("fruit_id int not null"));
    _db.CreateTable(table_name, column_container);
    table_name = "Albertsons";
}

void DatabaseTestSuite::CreateDuplicateTable()
{

    //Create table with same name.  (Should fail)
    QCOMPARE(_db.CreateTable(table_name, empty_container), false);
    QCOMPARE(_db.GetErrorOccurred(), true);

    QVector<QString> RecentError = _db.GetLastErrors();
    QCOMPARE(RecentError.size(), 1);
    QCOMPARE(RecentError.first(), QString("table Albertsons already exists Unable to execute statement"));
}

void DatabaseTestSuite::InsertObject()
{
    Fruit Banana("Banana");

    this->thread()->sleep(1);

    Fruit OtherBanana("Banana");

    QCOMPARE(_db.InsertObject(&Banana), true);

    //Duplicate Fruit Name, should not fail, different timestamp.
    QCOMPARE(_db.InsertObject(&OtherBanana), true);

    vector<Fruit> fruitBasket;
    fruitBasket.push_back(Banana);
    fruitBasket.push_back(OtherBanana);

    Basket TestBasket("Tester");

    QCOMPARE(_db.InsertObject(&TestBasket), true);

    for(int i = 0; i < fruitBasket.size(); i++)
    {
        QCOMPARE(_db.InsertJoinedObject(&TestBasket, &fruitBasket[i]), true);
    }

    //Duplicate Fruit, should fail since this is the exact same fruit.
    QCOMPARE(_db.InsertObject(&Banana), false);

    //Error should've occurred from the last method.
    QCOMPARE(_db.GetErrorOccurred(), true);

    QVector<QString> RecentError = _db.GetLastErrors();

    QCOMPARE(RecentError.size(), 1);
    QCOMPARE(RecentError.first(), QString("Duplicate Insert Was Attempted: SELECT * FROM Albertsons WHERE fruit_name like '%1' AND time_stamp = %2.")
             .arg(Banana.GetName())
             .arg(Banana.GetTime()));
}


void DatabaseTestSuite::SelectName()
{
    //Set to a timestamp that is set up above in the gui filtering
    Fruit NarrowSearch("Banana");
    NarrowSearch.SetTime(10000);

    Fruit BananaNameSearch("Banana");
    BananaNameSearch.SetTime(0);

    Fruit NoNameSearch("");
    NoNameSearch.SetTime(10000);

    Fruit CatchAllSearch("");
    CatchAllSearch.SetTime(0);

    QString strongQuery = NarrowSearch.SearchQuery();

    QString nameQuery = BananaNameSearch.SearchQuery();

    QString timeQuery = NoNameSearch.SearchQuery();

    QString looseQuery = CatchAllSearch.SearchQuery();

    QVector<QString> table_data = _db.SelectAllFields(table_name);

    foreach(QString item, table_data)
    {
        qDebug() << item;
    }
}

QTEST_APPLESS_MAIN(DatabaseTestSuite)

#include "tst_databasetestsuite.moc"
