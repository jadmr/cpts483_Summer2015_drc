#include "evaluation_table_test.h"

EVALUATION_TABLE_TEST::EVALUATION_TABLE_TEST() : DB_TEST_BASE()
{
}

void EVALUATION_TABLE_TEST::CheckCreateEvaluationTable()
{
    QCOMPARE(_db.CreateEvaluationTable(evaluationTableName), true);
    QCOMPARE(_db.DoesTableExist(evaluationTableName), true);
}

//TODO: Finish function
void EVALUATION_TABLE_TEST::CheckEvaluationColumn()
{
    QVERIFY2(evaluation_table_columns.size() > 0, "Person TestColumn Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(evaluationTableName);

    QVERIFY2(database_columns.size() > 0, "Person DatabaseColumn Vector Contains No Columns");
    QCOMPARE(evaluation_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, evaluation_table_columns, "VERIFY_PERSON_COLUMNS_DEBUG.txt");
    QCOMPARE(evaluation_table_columns, database_columns);
}

//TODO: Finish function
void EVALUATION_TABLE_TEST::CheckInsertEmptyEvaluationObject()
{

}

//TODO: Finish function
void EVALUATION_TABLE_TEST::CheckInsertFullEvaluationObject()
{

}

void EVALUATION_TABLE_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void EVALUATION_TABLE_TEST::cleanupTestCase()
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
