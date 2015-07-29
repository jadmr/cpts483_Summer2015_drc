#ifndef DB_TEST_BASE_H
#define DB_TEST_BASE_H

#include <QString>
#include <QtTest>
#include <QTextStream>
#include <QFile>

#include "drcdb.h"
#include "mediationprocess.h"
#include "Person.h"
#include "drctypes.h"
#include "client_column_enum.h"
#include "client_session_column_enum.h"
#include "mediation_evaluation_column_enum.h"
#include "note_column_enum.h"
#include "person_column_enum.h"
#include "process_column_enum.h"
#include "session_column_enum.h"

#define CONSTANTS {
#define INSERT_EMPTY_PERSON_DEBUG true
#define INSERT_FULL_PERSON_DEBUG true
#define INSERT_EMPTY_PROCESS_DEBUG true
#define INSERT_FULL_PROCESS_DEBUG true
#define INSERT_EMPTY_SESSION_DEBUG true
#define INSERT_FULL_SESSION_DEBUG true
#define INSERT_EMPTY_CLIENT_SESSION_DEBUG true
#define INSERT_FULL_CLIENT_SESSION_DEBUG true

#define TITLE_COLUMNS 45
#define DISTANCE_FROM_COLON -30
#define SMALLER_DISTANCE_BETWEEN 37
#define DISTANCE_BETWEEN_COLUMNS 45
#define FILL_CHARACTER ' '
#define CONSTANTS }

/*
 * This base class provides common methods across all unit tests
 */

class DB_TEST_BASE : public QObject
{

public:

    DB_TEST_BASE();

    void open_database();

    void OutputDebugInfo(QVector<QString> TableColumns, QVector<QString> FromDatabase, QVector<QString> FromFile, QString OutputFileName);
    void OutputColumnInfo(QVector<QString> DatabaseColumns, QVector<QString> TestColumns, QString OutputFileName);

    #define PRINT_FUNCTIONS {
    void PrintVectorStrings(QVector<QString> PrintThis);
    void PrintObjects();
    void PrintProcessObject(MediationProcess *object);
    void PrintSessionObject(MediationSession *object);
    void PrintClientObject(Party *object);
    void PrintPersonObject(Person *object);
    void PrintNoteObject(Note *object);
    #define PRINT_FUNCTIONS }

    #define INITIALIZATION_FUNCTIONS {
    Person* InitializePersonObject(QVector<QString> PersonStringValues);
    MediationProcess* InitializeProcessObject(QVector<QString> ProcessStringValues);
    MediationSession* InitializeSessionObject(QVector<QString> SessionStringValues);
    Party* InitializeClientObject(Person *Primary);
    ClientSessionData* InitializeClientSessionObject(QVector<QString> ClientSessionValues);
    Note* InitializeNoteObject(QVector<QString> NoteStringValues);
    MediationEvaluation* InitializeEvaluationObject(QVector<QString> values);

    MediationProcess* InitializeEntireMediationProcess();
    #define INITIALIZATION_METHODS }

    #define ALLOCATION_FUNCTIONS {
    void AllocateTableNames();
    void AllocateVectorValues();
    void AllocateTableColumns();

    void AllocatePersonColumns();
    void AllocateProcessColumns();
    void AllocateSessionColumns();
    void AllocateClientColumns();
    void AllocateClientSessionColumns();
    void AllocateNotesColumns();
    void AllocateEvaluationColumns();

    void AllocateEmptyPersonVector();
    void AllocateFullPersonVector();

    void AllocateEmptyProcessVector();
    void AllocateFullProcessVector();

    void AllocateEmptySessionVector();
    void AllocateFullSessionVector();

    void AllocateEmptyClientVector();
    void AllocateFullClientVector();

    void AllocateEmptyClientSessionVector();
    void AllocateFullClientSessionVector();

    void AllocateEmptyNoteValues();
    void AllocateFullNoteValues();

    void AllocateEmptyEvaluationVector();
    #define ALLOCATION_METHODS }

protected:
    DRCDB _db;

    #define TRACKERS {

    //These trackers take care of the clean up
    QVector<Person*> PersonObjectsTracker;
    QVector<MediationProcess*> ProcessObjectsTracker;
    QVector<MediationSession*> SessionObjectsTracker;
    QVector<Party*> PartyObjectsTracker;
    QVector<ClientSessionData*> ClientSessionObjectsTracker;
    QVector<Note*> NoteObjectsTracker;
    QVector<MediationEvaluation*> MediationEvaluationObjectsTracker;
    #define TRACKERS }

    #define TABLE_FIELDS {
    const QString DateFormat;
    const QString DateTimeFormat;
    const QString TimeFormat;

    QString database_name;

    QString person_table_name;
    QString mediation_table_name;
    QString session_table_name;
    QString client_table_name;
    QString notes_table_name;
    QString client_session_table_name;
    QString user_table_name;
    QString evaluationTableName;

    QVector<QString> person_table_columns;
    QVector<QString> mediation_table_columns;
    QVector<QString> session_table_columns;
    QVector<QString> client_table_columns;
    QVector<QString> client_session_table_columns;
    QVector<QString> notes_table_columns;
    QVector<QString> evaluation_table_columns;

    QVector<QString> empty_person_values;
    QVector<QString> full_person_values;

    QVector<QString> empty_process_values;
    QVector<QString> full_process_values;

    QVector<QString> empty_session_values;
    QVector<QString> full_session_values;

    QVector<QString> empty_client_values;
    QVector<QString> full_client_values;

    QVector<QString> empty_client_session_values;
    QVector<QString> full_client_session_values;

    QVector<QString> empty_note_values;
    QVector<QString> full_note_values;

    QVector<QString> empty_evaluation_values;
    QVector<QString> full_evaluation_values;

    Person* EmptyPerson;
    Person* FullPerson;

    MediationProcess* EmptyProcess;
    MediationProcess* FullProcess;

    MediationSession* EmptySession;
    MediationSession* FullSession;

    Party* EmptyParty;
    Party* FullParty;

    ClientSessionData* EmptyClientSession;
    ClientSessionData* FullClientSession;

    Note* EmptyNote;
    Note* FullNote;

    MediationEvaluation* EmptyEvaluation;
    MediationEvaluation* FullEvaluation;
    #define TABLE_FIELDS }
};

#endif // DB_TEST_BASE_H

