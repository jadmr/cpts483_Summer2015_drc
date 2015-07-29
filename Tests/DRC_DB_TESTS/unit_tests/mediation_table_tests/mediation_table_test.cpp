#include "mediation_table_test.h"

MEDIATION_TABLE_TEST::MEDIATION_TABLE_TEST() : DB_TEST_BASE()
{

}

void MEDIATION_TABLE_TEST::CheckCreateMediationTable()
{
    QCOMPARE(_db.CreateMediationTable(mediation_table_name), true);
    QCOMPARE(_db.DoesTableExist(mediation_table_name), true);
}

void MEDIATION_TABLE_TEST::CheckProcessColumn()
{
    QVERIFY2(mediation_table_columns.size() > 0, "Mediation Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(mediation_table_name);

    QVERIFY2(database_columns.size() > 0, "Mediation DatabaseColumn Vector Contains No Columns");
    QCOMPARE(mediation_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, mediation_table_columns, "VERIFY_MEDIATION_COLUMNS_DEBUG.txt");
    QCOMPARE(mediation_table_columns, database_columns);
}

void MEDIATION_TABLE_TEST::CheckInsertEmptyProcessObject()
{
    QCOMPARE(_db.InsertObject(EmptyProcess), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(mediation_table_name, "Process_id", 1);
    QCOMPARE(EmptyResults.size(), empty_process_values.size());

    if(INSERT_EMPTY_PROCESS_DEBUG)
        OutputDebugInfo(mediation_table_columns, EmptyResults, empty_process_values, "INSERT_EMPTY_PROCESS_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_process_values);
}

void MEDIATION_TABLE_TEST::CheckInsertFullProcessObject()
{
    QCOMPARE(_db.InsertObject(FullProcess),true);

    QVector<QString> FullResults = _db.SelectOneFields(mediation_table_name, "Process_id", 2);

    if(INSERT_FULL_PROCESS_DEBUG)
        OutputDebugInfo(mediation_table_columns, FullResults, full_process_values, "INSERT_FULL_PROCESS_DEBUG.txt");

    QCOMPARE(full_process_values, FullResults);
}

void MEDIATION_TABLE_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void MEDIATION_TABLE_TEST::cleanupTestCase()
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
