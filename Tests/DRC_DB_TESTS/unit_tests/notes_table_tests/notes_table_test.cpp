#include "notes_table_test.h"

NOTES_TABLE_TEST::NOTES_TABLE_TEST() : DB_TEST_BASE()
{
}

void NOTES_TABLE_TEST::CheckCreateNotesTable()
{
    QCOMPARE(_db.CreateNotesTable(notes_table_name), true);
    QCOMPARE(_db.DoesTableExist(notes_table_name), true);
}

void NOTES_TABLE_TEST::CheckNotesColumn()
{
    QVERIFY2(notes_table_columns.size() > 0, "Notes Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(notes_table_name);

    QVERIFY2(database_columns.size() > 0, "Notes DatabaseColumn Vector Contains No Columns");
    QCOMPARE(notes_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, notes_table_columns, "VERIFY_NOTES_COLUMNS_DEBUG.txt");
    QCOMPARE(notes_table_columns, database_columns);
}

void NOTES_TABLE_TEST::CheckInsertEmptyNoteObject()
{
//    EmptyNote.SetMediationId(EmptyProcess->GetId());
//    EmptyNote.SetSessionId(EmptySession->GetId());
//    EmptyNote.SetMessage(                                                       empty_note_values[3]);
//    EmptyNote.SetCreatedDate(           QDateTime::fromString(                  empty_note_values[4], DateTimeFormat));

    QCOMPARE(_db.InsertObject(EmptyNote), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(notes_table_name, "Note_id", 1);

    QCOMPARE(EmptyResults.size(), empty_note_values.size());

    if(INSERT_EMPTY_CLIENT_SESSION_DEBUG)
        OutputDebugInfo(notes_table_columns, EmptyResults, empty_note_values, "INSERT_EMPTY_NOTE_DEBUG.txt");

     QCOMPARE(EmptyResults, empty_note_values);
}

void NOTES_TABLE_TEST::CheckInsertFullNoteObject()
{
//    FullNote.SetMediationId(FullProcess->GetId());
//    FullNote.SetSessionId(FullSession->GetId());
//    FullNote.SetMessage(                                                        full_note_values[3]);
//    FullNote.SetCreatedDate(             QDateTime::fromString(                 full_note_values[4], DateTimeFormat));

    QCOMPARE(_db.InsertObject(FullNote), true);

    QVector<QString> FullResults = _db.SelectOneFields(notes_table_name, "Note_id", 2);

    QCOMPARE(FullResults.size(), full_note_values.size());

    if(INSERT_EMPTY_CLIENT_SESSION_DEBUG)
        OutputDebugInfo(notes_table_columns, FullResults, full_note_values, "INSERT_FULL_NOTE_DEBUG.txt");

    QCOMPARE(FullResults, full_note_values);
}

void NOTES_TABLE_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void NOTES_TABLE_TEST::cleanupTestCase()
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
