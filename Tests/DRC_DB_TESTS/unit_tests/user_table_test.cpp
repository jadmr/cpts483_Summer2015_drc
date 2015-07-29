#include "user_table_tests/user_table_test.h"

USER_TABLE_TEST::USER_TABLE_TEST() :  DB_TEST_BASE()
{
}

void USER_TABLE_TEST::CheckCreateUserTable()
{
    QCOMPARE(_db.CreateUserTable(user_table_name), true);
    QCOMPARE(_db.DoesTableExist(user_table_name), true);
}

void USER_TABLE_TEST::CheckUserColumn()
{
    QVERIFY2(user_table_columns.size() > 0, "Person TestColumn Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(user_table_name);

    QVERIFY2(database_columns.size() > 0, "Person DatabaseColumn Vector Contains No Columns");
    QCOMPARE(user_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, user_table_columns, "VERIFY_PERSON_COLUMNS_DEBUG.txt");
    QCOMPARE(user_table_columns, database_columns);
}

//TODO: Finish function
void USER_TABLE_TEST::CheckInsertEmptyUserObject()
{

}

//TODO: Finish function
void USER_TABLE_TEST::CheckInsertFullUserObject()
{

}


void USER_TABLE_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void USER_TABLE_TEST::cleanupTestCase()
{
    //Database should've closed successfully.
    QCOMPARE(_db.CloseDatabase(), true);

    foreach(Person* object, PersonObjectsTracker)
    {
        delete object;
        object = nullptr;
    }

    foreach(MediationProcess* object, ProcessObjectsTracker)
    {
        delete object;
        object = nullptr;
    }

    foreach(MediationSession* object, SessionObjectsTracker)
    {
        delete object;
        object = nullptr;
    }

    foreach(Party* object, PartyObjectsTracker)
    {
        object->SetPrimary(nullptr);
        delete object;
        object = nullptr;
    }

    foreach(ClientSessionData* object, ClientSessionObjectsTracker)
    {
        delete object;
        object = nullptr;
    }

    foreach(Note* object, NoteObjectsTracker)
    {
        delete object;
        object = nullptr;
    }

    foreach(MediationEvaluation* object, MediationEvaluationObjectsTracker)
    {
        delete object;
        object = nullptr;
    }

    //*******For the sake of this Test Suite, we delete database after every run.*******
    //*******Comment out if undesirable; IE, looking inside file directly.       *******
    //*******Be sure to manually delete if you do comment this line out.         *******

    //QCOMPARE(QFile::remove(database_name), true);
}
