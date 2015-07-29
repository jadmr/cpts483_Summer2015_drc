#include "person_table_test.h"

PERSON_TABLE_TEST::PERSON_TABLE_TEST() : DB_TEST_BASE()
{

}


void PERSON_TABLE_TEST::CheckCreatePersonTable()
{
    QCOMPARE(_db.CreatePersonTable(person_table_name), true);
    QCOMPARE(_db.DoesTableExist(person_table_name), true);
}

void PERSON_TABLE_TEST::CheckPersonColumn()
{
    QVERIFY2(person_table_columns.size() > 0, "Person TestColumn Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(person_table_name);

    QVERIFY2(database_columns.size() > 0, "Person DatabaseColumn Vector Contains No Columns");
    QCOMPARE(person_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, person_table_columns, "VERIFY_PERSON_COLUMNS_DEBUG.txt");
    QCOMPARE(person_table_columns, database_columns);
}

void PERSON_TABLE_TEST::CheckInsertEmptyPersonObject()
{
    QCOMPARE(_db.InsertObject(EmptyPerson), true);
    QVector<QString> EmptyResults = _db.SelectOneFields(person_table_name, "Person_id", 1);
    QVector<QString> TruncatedEmpty = empty_person_values.mid(0,15);
    QCOMPARE(TruncatedEmpty.size(), EmptyResults.size());

    if(INSERT_EMPTY_PERSON_DEBUG)
        OutputDebugInfo(person_table_columns, EmptyResults, TruncatedEmpty, "INSERT_EMPTY_PERSON_DEBUG.txt");

    QCOMPARE(TruncatedEmpty, EmptyResults);
}

void PERSON_TABLE_TEST::CheckInsertFullPersonObject()
{
    QCOMPARE(_db.InsertObject(FullPerson), true);
    QVector<QString> FullResults = _db.SelectOneFields(person_table_name, "Person_id", 2);

    QCOMPARE(15, FullResults.size());

    QVector<QString> TruncatedPerson = full_person_values.mid(0,15);

    QCOMPARE(FullResults.size(), TruncatedPerson.size());

    if (INSERT_FULL_PERSON_DEBUG)
        OutputDebugInfo(person_table_columns, FullResults, TruncatedPerson, "INSERT_FULL_PERSON_DEBUG.txt");

    QCOMPARE(TruncatedPerson, FullResults);
}

void PERSON_TABLE_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void PERSON_TABLE_TEST::cleanupTestCase()
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
