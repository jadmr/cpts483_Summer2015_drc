#include "client_session_table_test.h"

CLIENT_SESSION_TABLE_TEST::CLIENT_SESSION_TABLE_TEST() : DB_TEST_BASE()
{
}

void CLIENT_SESSION_TABLE_TEST::CheckCreateClientSessionTable()
{
    QCOMPARE(_db.CreateClientSessionTable(client_session_table_name), true);
    QCOMPARE(_db.DoesTableExist(client_session_table_name), true);
}

void CLIENT_SESSION_TABLE_TEST::CheckClientSessionColumn()
{
    QVERIFY2(client_session_table_columns.size() > 0, "ClientSession Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(client_session_table_name);

    QVERIFY2(database_columns.size() > 0, "ClientSession DatabaseColumn Vector Contains No Columns");
    QCOMPARE(client_session_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, client_session_table_columns, "VERIFY_CLIENTSESSION_COLUMNS_DEBUG.txt");
    QCOMPARE(client_session_table_columns, database_columns);
}

void CLIENT_SESSION_TABLE_TEST::CheckInsertEmptyClientSessionObject()
{
    QCOMPARE(_db.InsertClientSessionData(EmptyClientSession, EmptySession->GetId(), EmptyParty->GetId()), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(client_session_table_name, "Data_id", 1);

    //PrintVectorStrings(EmptyResults);

    QCOMPARE(EmptyResults.size(), empty_client_session_values.size());

    if(INSERT_EMPTY_CLIENT_SESSION_DEBUG)
        OutputDebugInfo(client_session_table_columns, EmptyResults, empty_client_session_values, "INSERT_EMPTY_CLIENTSESSION_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_client_session_values);
}

void CLIENT_SESSION_TABLE_TEST::CheckInsertFullClientSessionObject()
{
    QCOMPARE(_db.InsertClientSessionData(FullClientSession, FullSession->GetId(), FullParty->GetId()), true);

    QVector<QString> FullResults = _db.SelectOneFields(client_session_table_name, "Data_id", 2);

    QCOMPARE(FullResults.size(), full_client_session_values.size());

    if(INSERT_FULL_CLIENT_SESSION_DEBUG)
        OutputDebugInfo(client_session_table_columns, FullResults, full_client_session_values, "INSERT_FULL_CLIENTSESSION_DEBUG.txt");

    QCOMPARE(FullResults, full_client_session_values);
}

void CLIENT_SESSION_TABLE_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void CLIENT_SESSION_TABLE_TEST::cleanupTestCase()
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
