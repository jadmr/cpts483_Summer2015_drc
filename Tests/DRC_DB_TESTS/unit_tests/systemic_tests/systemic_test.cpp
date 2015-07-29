#include "systemic_test.h"

SYSTEMIC_TEST::SYSTEMIC_TEST() : DB_TEST_BASE()
{
}

void SYSTEMIC_TEST::CheckInsertEntireMediationObject()
{
    MediationProcess* Full = InitializeEntireMediationProcess();
    MediatorArg arg;
    arg.SetArg(Full);
    _db.InsertMediation(arg);
    QCOMPARE(arg.IsSuccessful(), true);
}

void SYSTEMIC_TEST::initTestCase()
{
    QFile::remove(database_name);
}

void SYSTEMIC_TEST::cleanupTestCase()
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
