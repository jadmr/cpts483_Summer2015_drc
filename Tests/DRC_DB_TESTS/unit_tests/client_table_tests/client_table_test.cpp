#include "client_table_test.h"

CLIENT_TABLE_TEST::CLIENT_TABLE_TEST() : DB_TEST_BASE()
{
}

void CLIENT_TABLE_TEST::CheckCreateClientTable()
{
    QCOMPARE(_db.CreateClientTable(client_table_name), true);
    QCOMPARE(_db.DoesTableExist(client_table_name), true);
}

void CLIENT_TABLE_TEST::CheckClientColumn()
{
    QVERIFY2(client_table_columns.size() > 0, "Client Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(client_table_name);

    QVERIFY2(database_columns.size() > 0, "Client DatabaseColumn Vector Contains No Columns");
    QCOMPARE(client_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, client_table_columns, "VERIFY_CLIENT_COLUMNS_DEBUG.txt");
    QCOMPARE(client_table_columns, database_columns);
}

void CLIENT_TABLE_TEST::CheckInsertEmptyClientObject()
{
    QCOMPARE(_db.InsertClientObject(EmptyProcess, EmptyParty), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(client_table_name, "Client_id", 1);

    QCOMPARE(EmptyResults.size(), empty_client_values.size());

    if(INSERT_FULL_SESSION_DEBUG)
        OutputDebugInfo(client_table_columns, EmptyResults, empty_client_values, "INSERT_EMPTY_CLIENT_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_client_values);
}

void CLIENT_TABLE_TEST::CheckInsertFullClientObject()
{
    QCOMPARE(_db.InsertClientObject(FullProcess, FullParty), true);

    QVector<QString> FullResults = _db.SelectOneFields(client_table_name, "Client_id", 2);

    QCOMPARE(FullResults.size(), full_client_values.size());

    if(INSERT_FULL_SESSION_DEBUG)
        OutputDebugInfo(client_table_columns, FullResults, full_client_values, "INSERT_FULL_CLIENT_DEBUG.txt");

    QCOMPARE(FullResults, full_client_values);
}

void CLIENT_TABLE_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void CLIENT_TABLE_TEST::cleanupTestCase()
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
