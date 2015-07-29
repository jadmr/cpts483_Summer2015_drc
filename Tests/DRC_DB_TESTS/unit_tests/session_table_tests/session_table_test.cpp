#include "session_table_test.h"

SESSION_TABLE_TEST::SESSION_TABLE_TEST() : DB_TEST_BASE()
{
}

void SESSION_TABLE_TEST::CheckCreateSessionTable()
{
    QCOMPARE(_db.CreateSessionTable(session_table_name), true);
    QCOMPARE(_db.DoesTableExist(session_table_name), true);
}

void SESSION_TABLE_TEST::CheckSessionColumn()
{
    QVERIFY2(session_table_columns.size() > 0, "Session Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(session_table_name);

    QVERIFY2(database_columns.size() > 0, "Session DatabaseColumn Vector Contains No Columns");
    QCOMPARE(session_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, session_table_columns, "VERIFY_SESSION_COLUMNS_DEBUG.txt");
    QCOMPARE(session_table_columns, database_columns);
}

void SESSION_TABLE_TEST::CheckInsertEmptySessionObject()
{
    QCOMPARE(_db.InsertLinkedObject(EmptyProcess->GetId(), EmptySession), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(session_table_name, "Session_id", 1);

    QCOMPARE(EmptyResults.size(), empty_session_values.size());

    if(INSERT_EMPTY_SESSION_DEBUG)
        OutputDebugInfo(session_table_columns, EmptyResults, empty_session_values, "INSERT_EMPTY_SESSION_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_session_values);
}

void SESSION_TABLE_TEST::CheckInsertFullSessionObject()
{
    QCOMPARE(_db.InsertLinkedObject(FullProcess->GetId(), FullSession), true);

    QVector<QString> FullResults = _db.SelectOneFields(session_table_name, "Session_id", 2);

    QCOMPARE(FullResults.size(), empty_session_values.size());

    if(INSERT_FULL_SESSION_DEBUG)
        OutputDebugInfo(session_table_columns, FullResults, full_session_values, "INSERT_FULL_SESSION_DEBUG.txt");

    QCOMPARE(FullResults, full_session_values);
}

void SESSION_TABLE_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void SESSION_TABLE_TEST::cleanupTestCase()
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
