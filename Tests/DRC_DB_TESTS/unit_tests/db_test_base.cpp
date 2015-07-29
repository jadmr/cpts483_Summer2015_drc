#include "db_test_base.h"

DB_TEST_BASE::DB_TEST_BASE() : DateFormat("yyyy-MM-dd"), DateTimeFormat("yyyy-MM-dd hh:mm:ss"), TimeFormat("hh:mm:ss")
{
    database_name = QString("drc_db.db3");
    open_database();

    AllocateTableNames();

    AllocateTableColumns();

    AllocateVectorValues();

    //Write method that accepts vector, and inserts into DB Object
    FullPerson = InitializePersonObject(full_person_values);
    EmptyPerson = InitializePersonObject(empty_person_values);

    EmptyProcess = InitializeProcessObject(empty_process_values);
    FullProcess = InitializeProcessObject(full_process_values);

    EmptySession = InitializeSessionObject(empty_session_values);
    FullSession = InitializeSessionObject(full_session_values);

    EmptyParty = InitializeClientObject(EmptyPerson);
    FullParty = InitializeClientObject(FullPerson);

    EmptyClientSession = InitializeClientSessionObject(empty_client_session_values);
    FullClientSession = InitializeClientSessionObject(full_client_session_values);

    EmptyNote = InitializeNoteObject(empty_note_values);
    FullNote = InitializeNoteObject(full_note_values);

    EmptyEvaluation = InitializeEvaluationObject(empty_evaluation_values);
}

void DB_TEST_BASE::open_database()
{
    _db.OpenDatabase(database_name);
}

void DB_TEST_BASE::AllocateTableColumns()
{
    AllocatePersonColumns();
    AllocateProcessColumns();
    AllocateSessionColumns();
    AllocateClientColumns();
    AllocateClientSessionColumns();
    AllocateNotesColumns();
    AllocateEvaluationColumns();
    AllocateUserColumns();

}

void DB_TEST_BASE::AllocateVectorValues()
{
    AllocateEmptyPersonVector();
    AllocateFullPersonVector();

    AllocateEmptyProcessVector();
    AllocateFullProcessVector();

    AllocateEmptySessionVector();
    AllocateFullSessionVector();

    AllocateEmptyClientVector();
    AllocateFullClientVector();

    AllocateEmptyClientSessionVector();
    AllocateFullClientSessionVector();

    AllocateEmptyNoteValues();
    AllocateFullNoteValues();

    AllocateEmptyUserValues();

    AllocateEmptyEvaluationVector();
}

MediationProcess* DB_TEST_BASE::InitializeEntireMediationProcess()
{
    MediationProcess* object = InitializeProcessObject(full_process_values);
    object->AddParty(InitializeClientObject(InitializePersonObject(full_person_values)));
    //object->AddParty(InitializeClientObject(InitializePersonObject(empty_person_values)));

    MediationSessionVector* sessions = new MediationSessionVector;
    MediationSession *pointer = InitializeSessionObject(full_session_values);
    pointer->addClientSessionData(InitializeClientSessionObject(full_client_session_values));

    sessions->push_back(pointer);

    object->setMediationSessionVector(sessions);

    return object;
}

Note* DB_TEST_BASE::InitializeNoteObject(QVector<QString> NoteStringValues)
{
    Note* object = new Note;
    NoteObjectsTracker.push_back(object);

    object->SetMediationId(                                                    NoteStringValues[NOTE_PROCESS_ID].toInt());
    object->SetSessionId(                                                      NoteStringValues[NOTE_SESSION_ID].toInt());
    object->SetMessage(                                                        NoteStringValues[NOTE]);
    object->SetCreatedDate(             QDateTime::fromString(                 NoteStringValues[CREATEDATE], DateTimeFormat));

    return object;
}

MediationEvaluation* DB_TEST_BASE::InitializeEvaluationObject(QVector<QString> values)
{
    //TODO: Finish initialize function. The issue with this function is that the Yes/No/Somewhat values seem to be
    //stored differently in the database than in the mediationEvaluation object

    MediationEvaluation* object = new MediationEvaluation;
    //This tracker takes care of the clean up
    MediationEvaluationObjectsTracker.push_back(object);

//    FAIRYES = 4,
//    FAIRNO = 5,
//    FAIRSOMEWHAT = 6,
//    IMPROVEYES = 7,
//    IMPROVENO = 8,
//    IMPROVESOMEWHAT = 9,
//    COMMUNICATEYES = 10,
//    COMMUNICATENO = 11,
//    COMMUNICATESOMEWHAT = 12,
//    UNDERSTANDYES = 13,
//    UNDERSTANDNO = 14,
//    UNDERSTANDSOMEWHAT = 15,
//    RECOMMENDYES = 16,
//    RECOMMENDNO = 17,
//    RECOMMENDSOMEWHAT = 18,
//    AGREEMENTYES = 19,
//    AGREEMENTNO = 20,
//    AGREEMENTSOMEWHAT = 21

    return object;
}

ClientSessionData* DB_TEST_BASE::InitializeClientSessionObject(QVector<QString> ClientSessionValues)
{
    ClientSessionData* object = new ClientSessionData;
    ClientSessionObjectsTracker.push_back(object);

    object->setIncome(                                                ClientSessionValues[INCOME]); //income
    object->setFee(                                                   ClientSessionValues[FEESCHARGED]); //feesCharged
    object->setPaid(           (bool)                                 ClientSessionValues[FEESPAID].toInt()); //feesPaid
    object->setAttySaidAttend( (bool)                                 ClientSessionValues[ATTORNEYEXPECTED].toInt()); //AttorneyExpected
    object->setAttyDidAttend(  (bool)                                 ClientSessionValues[ATTORNEYATTENDED].toInt()); //AttorneyAttended
    object->setSupport(                                               ClientSessionValues[SUPPORT].toInt()); //Support
    object->setOnPhone(        (bool)                                 ClientSessionValues[CLIENTPHONE].toInt()); //ClientPhone
    object->setAtTable(        (bool)                                 ClientSessionValues[ATTABLE].toInt()); //AtTable

    return object;
}

Party* DB_TEST_BASE::InitializeClientObject(Person* Primary)
{
    Party* object = new Party;
    PartyObjectsTracker.push_back(object);

    object->SetPrimary(Primary);

    return object;
}

MediationSession* DB_TEST_BASE::InitializeSessionObject(QVector<QString> SessionStringValues)
{
    MediationSession* object = new MediationSession;
    SessionObjectsTracker.push_back(object);

    object->SetState(               (SessionStates)                         SessionStringValues[SESSIONSTATUS].toInt());
    object->setOutcome(             (SessionOutcomes)                       SessionStringValues[SESSIONOUTCOME].toInt());
    object->SetCreatedDate(         QDateTime::fromString(                  SessionStringValues[SESSION_CREATEDDATETIME], DateTimeFormat));
    object->SetUpdatedDate(         QDateTime::fromString(                  SessionStringValues[SESSION_UPDATEDDATETIME], DateTimeFormat));
    object->setScheduledDate(       QDate::fromString(                      SessionStringValues[SCHEDULEDTIME].split(" ")[0], DateFormat));
    object->setScheduledTime(       QTime::fromString(                      SessionStringValues[SCHEDULEDTIME].split(" ")[1], TimeFormat));
    object->setMediator1(                                                   SessionStringValues[MEDIATOR1]);
    object->setMediator2(                                                   SessionStringValues[MEDIATOR2]);
    object->setObserver1(                                                   SessionStringValues[OBSERVER1]);
    object->setObserver2(                                                   SessionStringValues[OBSERVER2]);
    object->SetIsShuttle(           (bool)                                  SessionStringValues[SHUTTLE].toInt());

    return object;
}

MediationProcess* DB_TEST_BASE::InitializeProcessObject(QVector<QString> ProcessStringValues)
{
    MediationProcess* object = new MediationProcess;
    ProcessObjectsTracker.push_back(object);

    object->SetDisputeType(              (DisputeTypes)                      ProcessStringValues[DISPUTETYPE].toInt());
    object->SetCreatedDate(              QDateTime::fromString(              ProcessStringValues[PROCESS_CREATIONDATETIME], QString("yyyy-MM-dd hh:mm:ss")));
    object->SetUpdatedDate(              QDateTime::fromString(              ProcessStringValues[PROCESS_UPDATEDDATETIME], QString("yyyy-MM-dd hh:mm:ss")));
    object->SetState(                    (DisputeProcessStates)              ProcessStringValues[DISPUTESTATE].toInt());                  //DisputeProcessStates - PROCESS_STATE_SCHEDULED
    object->SetInternalState(            (DisputeProcessInternalStates)      ProcessStringValues[DISPUTEINTERNALSTATE].toInt());  //DisputeProcessInternalStates - PROCESS_INTERNAL_STATE_SCHEDULED
    object->SetCountyId(                 (CountyIds)                         ProcessStringValues[DISPUTECOUNTY].toInt());                          //CountyIds - COUNTY_BENTON
    object->SetReferralType(             (ReferralTypes)                     ProcessStringValues[REFERALSOURCE].toInt());                  //ReferralTypes - REFERRAL_T_PHONEBOOK
    object->SetInquiryTypes(             (InquiryTypes)                      ProcessStringValues[INQUIRYTYPE].toInt());                   //InquiryTypes - INQUIRY_T_WALKIN
    object->SetInfoOnly(                 (bool)                              ProcessStringValues[INFOONLY].toInt());                               //Info Only - FALSE
    object->SetIsCourtCase(              (bool)                              ProcessStringValues[ISCOURTCASE].toInt());                           //Is Court Case - TRUE
    object->SetCourtDate(                QDate::fromString(                  ProcessStringValues[COURTDATE], DateFormat));
    object->SetCourtType(                (CourtCaseTypes)                    ProcessStringValues[COURTCASETYPE].toInt());                   //CourtCaseTypes - COURT_T_SUPERIOR
    object->SetCourtOrder(                                                   ProcessStringValues[COURTORDERTYPE]);
    object->SetRequiresSpanish(          (bool)                              ProcessStringValues[TRANSLATORREQUIRED].toInt());
    object->SetSessionType(              (SessionTypes)                      ProcessStringValues[SESSIONTYPE].toInt());
    object->setMediationClause(          (bool)                              ProcessStringValues[MEDIATIONCLAUSE].toInt());
    object->SetIndirectChildren(         (int)                               ProcessStringValues[INDIRECTCHILDREN].toInt() );
    object->SetDirectChildren(           (int)                               ProcessStringValues[DIRECTCHILDREN].toInt() );
    object->SetIndirectAdult(            (int)                               ProcessStringValues[INDIRECTADULT].toInt() );
    object->SetDirectAdult(              (int)                               ProcessStringValues[DIRECTADULT].toInt() );
    object->SetTags(                     (QString)                           ProcessStringValues[PROCESS_TAGS] );

    return object;
}

Person* DB_TEST_BASE::InitializePersonObject(QVector<QString> PersonStringValues)
{
    Person* object = new Person;
    PersonObjectsTracker.push_back(object);

    object->setFirstName(                                                     PersonStringValues[FIRST_NAME]);
    object->setMiddleName(                                                    PersonStringValues[MIDDLE_NAME]);
    object->setLastName(                                                      PersonStringValues[LAST_NAME]);
    object->setStreet(                                                        PersonStringValues[STREET_NAME]);
    object->setUnit(                                                          PersonStringValues[UNIT_NAME]);
    object->setCity(                                                          PersonStringValues[CITY_NAME]);
    object->setState(                                                         PersonStringValues[STATE_NAME]);
    object->setZip(                                                           PersonStringValues[ZIP_CODE]);
    object->setCounty((CountyIds)                                             PersonStringValues[COUNTY_NAME].toInt());
    object->setPrimaryPhone(                                                  PersonStringValues[PRIMARY_PHONE]);
    object->setPrimaryPhoneExt(                                               PersonStringValues[PRIMARY_PHONE_EXT]);
    object->setSecondaryPhone(                                                PersonStringValues[SECONDARY_PHONE]);
    object->setSecondaryPhoneExt(                                             PersonStringValues[SECONDARY_PHONE_EXT]);
    object->setEmail(                                                         PersonStringValues[EMAIL_ADDRESS]);
    object->setNumberInHousehold(                                             PersonStringValues[NUMBERINHOUSEHOLD].toInt());
    object->setNumberChildrenInHousehold(                                     PersonStringValues[NUMBERCHILDRENINHOUSEHOLD].toInt());
    object->setAttorney(                                                      PersonStringValues[ATTORNEY]);
    object->setAttorneyPhone(                                                 PersonStringValues[ATTORNEYPHONE]);
    object->SetAttorneyEmail(                                                 PersonStringValues[ATTORNEYEMAIL]);
    object->setAssistantName(                                                 PersonStringValues[ASSISTANTNAME]);
    object->setAssistantPhone(                                                PersonStringValues[ASSISTANTPHONE]);
    object->setAssistantEmail(                                                PersonStringValues[ASSISTANTEMAIL]);

    return object;
}

void DB_TEST_BASE::PrintObjects()
{
    PrintPersonObject(FullPerson);
    PrintClientObject(FullParty);
    PrintSessionObject(FullSession);
    PrintNoteObject(FullNote);
    PrintProcessObject(FullProcess);
}

void DB_TEST_BASE::PrintProcessObject(MediationProcess *object)
{
    qDebug() << "Process Object:------------------------";
    qDebug() << object->GetId();
    qDebug() << object->GetDisputeType();
    qDebug() << object->GetCreatedDate().toString(DateTimeFormat);
    qDebug() << object->GetUpdatedDate().toString(DateTimeFormat);
    qDebug() << object->GetState();
    qDebug() << object->GetInternalState();
    qDebug() << object->GetCountyId();
    qDebug() << object->GetReferralType();
    qDebug() << object->GetInquiryType();
    qDebug() << object->GetInfoOnly();
    qDebug() << object->GetIsCourtCase();
    qDebug() << object->GetCourtDate().toString(DateFormat);
    qDebug() << object->GetCourtType();
    qDebug() << object->GetCourtOrder();
    qDebug() << object->GetRequiresSpanish();
    qDebug() << object->GetSessionType();
    qDebug() << object->getMediationClause();
}

void DB_TEST_BASE::PrintNoteObject(Note *object)
{
    qDebug() << "Note Object:---------------------------";
    qDebug() << object->GetId();
    qDebug() << object->GetmediationId();
    qDebug() << object->GetSessionId();
    qDebug() << object->GetMessage();
    qDebug() << object->GetCreatedDate().toString(DateFormat);
}

void DB_TEST_BASE::PrintSessionObject(MediationSession *object)
{
    qDebug() << "Session Object:------------------------";
    qDebug() << object->GetId();
    qDebug() << object->GetState();
    qDebug() << object->getOutcome();
    qDebug() << object->GetCreatedDate().toString(DateTimeFormat);
    qDebug() << object->GetUpdatedDate().toString(DateTimeFormat);
    qDebug() << object->getScheduledDate().toString(DateFormat);
    qDebug() << object->getScheduledTime().toString(TimeFormat);
    qDebug() << object->getMediator1();
    qDebug() << object->getMediator2();
    qDebug() << object->getObserver1();
    qDebug() << object->getObserver2();
    qDebug() << object->GetIsShuttle();
}

void DB_TEST_BASE::PrintClientObject(Party *object)
{
    qDebug() << "Party Object:---------------------------";
    qDebug() << object->GetId();
    qDebug() << object->GetPrimary()->getNumberInHousehold();
    qDebug() << object->GetPrimary()->getNumberChildrenInHousehold();
    qDebug() << object->GetPrimary()->getAttorney();
    qDebug() << object->GetPrimary()->getAttorneyPhone();
    qDebug() << object->GetPrimary()->getAttorneyEmail();
    qDebug() << object->GetPrimary()->getAssistantName();
    qDebug() << object->GetPrimary()->getAssistantPhone();
    qDebug() << object->GetPrimary()->getAssistantEmail();
}

void DB_TEST_BASE::PrintPersonObject(Person *object)
{
    qDebug() << "Person Object:--------------------------";
    qDebug() << object->GetId();
    qDebug() << object->getFirstName();
    qDebug() << object->getMiddleName();
    qDebug() << object->getLastName();
    qDebug() << object->getStreet();
    qDebug() << object->getUnit();
    qDebug() << object->getCity();
    qDebug() << object->getState();
    qDebug() << object->getZip();
    qDebug() << object->getCounty();
    qDebug() << object->getPrimaryPhone();
    qDebug() << object->getPrimaryPhoneExt();
    qDebug() << object->getSecondaryPhone();
    qDebug() << object->getSecondaryPhoneExt();
    qDebug() << object->getEmail();
}

void DB_TEST_BASE::OutputColumnInfo(QVector<QString> DatabaseColumns, QVector<QString> TestColumns, QString OutputFileName)
{
    QFile file(OutputFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << QString("%1%2\n")
        .arg(QString("Column read from Database"))
        .arg(QString("Column read from File"), SMALLER_DISTANCE_BETWEEN, QLatin1Char(FILL_CHARACTER));
    for (int index = 0 ; index < TestColumns.size() ; ++index)
    {
        out << QString("%1%2")
            .arg(QString("\"") + DatabaseColumns[index] + QString("\""))
            .arg(QString("\"") + TestColumns[index] + QString("\""), DISTANCE_BETWEEN_COLUMNS , QLatin1Char(FILL_CHARACTER));

        if(DatabaseColumns[index] == TestColumns[index])
            out << QString("\n\n");
        else
            out << QString("%1\n\n").arg("**ERROR**", DISTANCE_BETWEEN_COLUMNS, QLatin1Char(FILL_CHARACTER));
    }
}

void DB_TEST_BASE::OutputDebugInfo(QVector<QString> TableColumns, QVector<QString> FromDatabase, QVector<QString> FromFile, QString OutputFileName)
{
    QFile file(OutputFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << QString("%1%2\n")
        .arg(QString("Data read from Database"), TITLE_COLUMNS, QLatin1Char(FILL_CHARACTER))
        .arg(QString("Data read from File"), DISTANCE_BETWEEN_COLUMNS, QLatin1Char(FILL_CHARACTER));
    for (int index = 0 ; index < FromFile.size() ; ++index)
    {
        out << QString("%1%2%3")
            .arg(TableColumns[index] + QString(": "), DISTANCE_FROM_COLON, QLatin1Char(FILL_CHARACTER))
            .arg(QString("\"") + FromDatabase[index] + QString("\""))
            .arg(QString("\"") + FromFile[index] + QString("\""), DISTANCE_BETWEEN_COLUMNS , QLatin1Char(FILL_CHARACTER));

        if(FromDatabase[index] == FromFile[index])
            out << QString("\n\n");
        else
            out << QString("%1\n\n").arg("**ERROR**", DISTANCE_BETWEEN_COLUMNS, QLatin1Char(FILL_CHARACTER));
    }
}

void DB_TEST_BASE::PrintVectorStrings(QVector<QString> PrintThis)
{
    qDebug() << "Printing your damn Vector:";
    foreach (QString line, PrintThis)
        qDebug() << line;
    qDebug();
}

void DB_TEST_BASE::AllocateTableNames()
{
    person_table_name = QString("Person_Table");
    mediation_table_name = QString("Mediation_Table");
    session_table_name = QString("Session_Table");
    client_table_name = QString("Client_Table");
    notes_table_name = QString("Notes_Table");
    client_session_table_name = QString("Client_session_table");
    user_table_name = QString("User_Table");
    evaluationTableName = QString("Evaluation_Table");
}

void DB_TEST_BASE::AllocatePersonColumns()
{
    person_table_columns.push_back("Person_id");
    person_table_columns.push_back("first_name");
    person_table_columns.push_back("middle_name");
    person_table_columns.push_back("last_name");
    person_table_columns.push_back("street_name");
    person_table_columns.push_back("unit_name");
    person_table_columns.push_back("city_name");
    person_table_columns.push_back("state_name");
    person_table_columns.push_back("zip_code");
    person_table_columns.push_back("county_name");
    person_table_columns.push_back("primary_phone");
    person_table_columns.push_back("primary_phone_ext");
    person_table_columns.push_back("secondary_phone");
    person_table_columns.push_back("secondary_phone_ext");
    person_table_columns.push_back("email_address");
}

void DB_TEST_BASE::AllocateProcessColumns()
{
    mediation_table_columns.push_back("Process_id");
    mediation_table_columns.push_back("DisputeType");
    mediation_table_columns.push_back("CreationDate");
    mediation_table_columns.push_back("UpdatedDate");
    mediation_table_columns.push_back("CreationDateTime");
    mediation_table_columns.push_back("UpdatedDateTime");
    mediation_table_columns.push_back("DisputeState");
    mediation_table_columns.push_back("DisputeInternalState");
    mediation_table_columns.push_back("DisputeCounty");
    mediation_table_columns.push_back("ReferalSource");
    mediation_table_columns.push_back("InquiryType");
    mediation_table_columns.push_back("InfoOnly");
    mediation_table_columns.push_back("IsCourtCase");
    mediation_table_columns.push_back("CourtDate");
    mediation_table_columns.push_back("CourtCaseType");
    mediation_table_columns.push_back("CourtOrderType");
    mediation_table_columns.push_back("TranslatorRequired");
    mediation_table_columns.push_back("SessionType");
    mediation_table_columns.push_back("MediationClause");
    mediation_table_columns.push_back("IndirectChildren");
    mediation_table_columns.push_back("DirectChildren");
    mediation_table_columns.push_back("IndirectAdult");
    mediation_table_columns.push_back("DirectAdult");
    mediation_table_columns.push_back("Tags");
}

void DB_TEST_BASE::AllocateSessionColumns()
{
    session_table_columns.push_back("Session_id");
    session_table_columns.push_back("Process_id");
    session_table_columns.push_back("SessionStatus");
    session_table_columns.push_back("SessionOutcome");
    session_table_columns.push_back("CreatedDateTime");
    session_table_columns.push_back("UpdatedDateTime");
    session_table_columns.push_back("ScheduledTime");
    session_table_columns.push_back("Mediator1");
    session_table_columns.push_back("Mediator2");
    session_table_columns.push_back("Observer1");
    session_table_columns.push_back("Observer2");
    session_table_columns.push_back("Shuttle");
}

void DB_TEST_BASE::AllocateClientColumns()
{
    client_table_columns.push_back("Client_id");
    client_table_columns.push_back("Process_id");
    client_table_columns.push_back("Person_id");
    client_table_columns.push_back("Children");
    client_table_columns.push_back("Adult");
    client_table_columns.push_back("AttorneyName");
    client_table_columns.push_back("AttorneyPhone");
    client_table_columns.push_back("AttorneyEmail");
    client_table_columns.push_back("AssistantName");
    client_table_columns.push_back("AssistantPhone");
    client_table_columns.push_back("AssistantEmail");
}

void DB_TEST_BASE::AllocateClientSessionColumns()
{
    client_session_table_columns.push_back("Data_id");
    client_session_table_columns.push_back("Client_id");
    client_session_table_columns.push_back("Session_id");
    client_session_table_columns.push_back("income");
    client_session_table_columns.push_back("feesCharged");
    client_session_table_columns.push_back("feesPaid");
    client_session_table_columns.push_back("AttorneyExpected");
    client_session_table_columns.push_back("AttorneyAttended");
    client_session_table_columns.push_back("Support");
    client_session_table_columns.push_back("ClientPhone");
    client_session_table_columns.push_back("AtTable");
}

void DB_TEST_BASE::AllocateNotesColumns()
{
    notes_table_columns.push_back("Note_id");
    notes_table_columns.push_back("Process_id");
    notes_table_columns.push_back("Session_id");
    notes_table_columns.push_back("Note");
    notes_table_columns.push_back("CreateDate");
}

void DB_TEST_BASE::AllocateEvaluationColumns()
{
    evaluation_table_columns.push_back("Id");
    evaluation_table_columns.push_back("startDate");
    evaluation_table_columns.push_back("endDate");
    evaluation_table_columns.push_back("CountyId");
    evaluation_table_columns.push_back("FairYes");
    evaluation_table_columns.push_back("FairNo");
    evaluation_table_columns.push_back("FairSomewhat");
    evaluation_table_columns.push_back("ImproveYes");
    evaluation_table_columns.push_back("ImproveNo");
    evaluation_table_columns.push_back("ImproveSomewhat");
    evaluation_table_columns.push_back("CommunicateYes");
    evaluation_table_columns.push_back("CommunicateNo");
    evaluation_table_columns.push_back("CommunicateSomewhat");
    evaluation_table_columns.push_back("UnderstandYes");
    evaluation_table_columns.push_back("UnderstandNo");
    evaluation_table_columns.push_back("UnderstandSomewhat");
    evaluation_table_columns.push_back("RecommendYes");
    evaluation_table_columns.push_back("RecommendNo");
    evaluation_table_columns.push_back("RecommendSomewhat");
    evaluation_table_columns.push_back("AgreementYes");
    evaluation_table_columns.push_back("AgreementNo");
    evaluation_table_columns.push_back("AgreementSomewhat");
}

void DB_TEST_BASE::AllocateUserColumns()
{
    user_table_columns.push_back("user_id");
    user_table_columns.push_back("userName");
    user_table_columns.push_back("password");
    user_table_columns.push_back("Admin");
}

void DB_TEST_BASE::AllocateEmptyPersonVector()
{
    empty_person_values.push_back(QString("1"));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString("0"));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString("0"));
    empty_person_values.push_back(QString("0"));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
}

void DB_TEST_BASE::AllocateFullPersonVector()
{
    full_person_values.push_back(QString("2"));
    full_person_values.push_back(QString("Bruce"));
    full_person_values.push_back(QString("Chan"));
    full_person_values.push_back(QString("Lee"));
    full_person_values.push_back(QString("55555 Huntington Place"));
    full_person_values.push_back(QString("B"));
    full_person_values.push_back(QString("New York"));
    full_person_values.push_back(QString("Alaska"));
    full_person_values.push_back(QString("55555"));
    full_person_values.push_back(QString("2"));
    full_person_values.push_back(QString("111-111-1111"));
    full_person_values.push_back(QString("111"));
    full_person_values.push_back(QString("222-222-2222"));
    full_person_values.push_back(QString("222"));
    full_person_values.push_back(QString("EnterTheDragon@BruceLee.com"));
    full_person_values.push_back(QString("7"));
    full_person_values.push_back(QString("1000"));
    full_person_values.push_back(QString("Birdman"));
    full_person_values.push_back(QString("123-123-1234"));
    full_person_values.push_back(QString("Birdman@Attorney.law"));
    full_person_values.push_back(QString("Rachel Dawes"));
    full_person_values.push_back(QString("333-333-3333"));
    full_person_values.push_back(QString("MaskNotMe@Attorney.law"));
}

void DB_TEST_BASE::AllocateEmptyProcessVector()
{
    empty_process_values.push_back(QString("1"));                           //PROCESS_ID
    empty_process_values.push_back(QString("0"));                           //DISPUTETYPE
    empty_process_values.push_back(QString("2000-01-01"));                  //CREATIONDATE
    empty_process_values.push_back(QString("2000-01-01"));                  //UPDATEDDATE
    empty_process_values.push_back(QString("2000-01-01 12:00:01"));         //CREATIONDATETIME
    empty_process_values.push_back(QString("2000-01-01 12:00:01"));         //UPDATEDDATETIME
    empty_process_values.push_back(QString("0"));                           //DISPUTESTATE
    empty_process_values.push_back(QString("0"));                           //DISPUTEINTERNALSTATE
    empty_process_values.push_back(QString("1"));                           //DISPUTECOUNTY
    empty_process_values.push_back(QString("0"));                           //REFERALSOURCE
    empty_process_values.push_back(QString("0"));                           //INQUIRYTYPE
    empty_process_values.push_back(QString("0"));                           //INFOONLY
    empty_process_values.push_back(QString("0"));                           //ISCOURTCASE
    empty_process_values.push_back(QString("2000-01-01"));                  //COURTDATE
    empty_process_values.push_back(QString("0"));                           //COURTCASETYPE
    empty_process_values.push_back(QString(""));                            //COURTORDERTYPE
    empty_process_values.push_back(QString("0"));                           //TRANSLATORREQUIRED
    empty_process_values.push_back(QString("0"));                           //SESSIONTYPE
    empty_process_values.push_back(QString("0"));                           //MEDIATIONCLAUSE

    QVariant temp;
    temp = qlonglong(-1163005939);
    empty_process_values.push_back(QString(temp.toString()));                           //IndirectChildren
    empty_process_values.push_back(QString(temp.toString()));                           //DirectChildren
    empty_process_values.push_back(QString(temp.toString()));                           //IndirectAdult
    empty_process_values.push_back(QString(temp.toString()));                           //DirectAdult
    empty_process_values.push_back(QString(""));                                         //Tags

}

void DB_TEST_BASE::AllocateFullProcessVector()
{
    full_process_values.push_back("2");                     //Process ID
    full_process_values.push_back("8");                     //DisputeTypes - DISPUTE_T_WORKPLACE
    full_process_values.push_back("2014-07-24");            //Creation Date     QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    full_process_values.push_back("2014-07-25");            //Updated Date      QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    full_process_values.push_back("2014-07-24 12:00:01");   //Creation DateTime QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    full_process_values.push_back("2014-07-25 12:00:02");   //Updated DateTime  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    full_process_values.push_back("3");                     //DisputeProcessStates - PROCESS_STATE_SCHEDULED
    full_process_values.push_back("7");                     //DisputeProcessInternalStates - PROCESS_INTERNAL_STATE_SCHEDULED
    full_process_values.push_back("2");                     //CountyIds - COUNTY_BENTON
    full_process_values.push_back("14");                    //ReferralTypes - REFERRAL_T_PHONEBOOK
    full_process_values.push_back("4");                     //InquiryTypes - INQUIRY_T_WALKIN
    full_process_values.push_back("0");                     //Info Only - FALSE
    full_process_values.push_back("1");                     //Is Court Case - TRUE
    full_process_values.push_back("2015-07-22");            //COURT DATE
    full_process_values.push_back("2");                     //CourtCaseTypes - COURT_T_SUPERIOR
    full_process_values.push_back("Ultimate Fists of Fury!!!");                     //CourtOrderTypes
    full_process_values.push_back("1");                     //Is Spanish Required - TRUE
    full_process_values.push_back("1");                     //SessionTypes - MEDIATION_SESSION
    full_process_values.push_back("1");                     //MediationClause - TRUE
    full_process_values.push_back("1");                     //IndirectChildren
    full_process_values.push_back("2");                     //DirectChildren
    full_process_values.push_back("3");                     //IndirectAdult
    full_process_values.push_back("4");                     //DirectAdult
    full_process_values.push_back("B - xcc");               //Tags

}

void DB_TEST_BASE::AllocateEmptySessionVector()
{
    empty_session_values.push_back("1");                        //SESSION_ID
    empty_session_values.push_back("1");                        //PROCESS_ID
    empty_session_values.push_back("1");                        //SESSION_STATE - NONE
    empty_session_values.push_back("1");                        //SESSION_OUTCOME - NONE
    empty_session_values.push_back("2014-07-24 00:00:01");
    empty_session_values.push_back("2014-07-24 00:00:02");
    empty_session_values.push_back("2014-07-28 00:00:03");
    empty_session_values.push_back("MediatorNone1");
    empty_session_values.push_back("MediatorNone2");
    empty_session_values.push_back("ObserverNone1");
    empty_session_values.push_back("ObserverNone2");
    empty_session_values.push_back("0");
}

void DB_TEST_BASE::AllocateFullSessionVector()
{
    full_session_values.push_back("2");
    full_session_values.push_back("2");
    full_session_values.push_back("3");        //SESSION_STATE_CONFIRMED
    full_session_values.push_back("4");        //SESSION_OUTCOME_AGREEMENT
    full_session_values.push_back("2025-08-25 03:44:55");
    full_session_values.push_back("2025-08-26 06:00:00");
    full_session_values.push_back("2700-08-26 01:00:44");
    full_session_values.push_back("Ironfist");
    full_session_values.push_back("Luke Cage");
    full_session_values.push_back("Red Arrow");
    full_session_values.push_back("Bizzaro");
    full_session_values.push_back("1");
}

void DB_TEST_BASE::AllocateEmptyClientVector()
{
    empty_client_values.push_back("1");     //Client ID
    empty_client_values.push_back("1");     //Process ID
    empty_client_values.push_back("1");     //Person ID
    empty_client_values.push_back("0");     //Number of Children in Household
    empty_client_values.push_back("0");     //Number of Adults in Houeshold
    empty_client_values.push_back("");      //Attorney Name
    empty_client_values.push_back("");      //Attorney Phone
    empty_client_values.push_back("");      //Attorney Email
    empty_client_values.push_back("");      //Assistant Name
    empty_client_values.push_back("");      //Assistant Phone
    empty_client_values.push_back("");      //Assistant Email
}

void DB_TEST_BASE::AllocateFullClientVector()
{
    full_client_values.push_back("2");     //Client ID
    full_client_values.push_back("2");     //Process ID
    full_client_values.push_back("2");     //Person ID
    full_client_values.push_back("1000");     //Number of Children in Household
    full_client_values.push_back("7");     //Number of Adults in Houeshold
    full_client_values.push_back("Birdman");      //Attorney Name
    full_client_values.push_back("123-123-1234");      //Attorney Phone
    full_client_values.push_back("Birdman@Attorney.law");      //Attorney Email
    full_client_values.push_back("Rachel Dawes");      //Assistant Name
    full_client_values.push_back("333-333-3333");      //Assistant Phone
    full_client_values.push_back("MaskNotMe@Attorney.law");      //Assistant Email
}

void DB_TEST_BASE::AllocateEmptyClientSessionVector()
{
    empty_client_session_values.push_back("1");
    empty_client_session_values.push_back("1");
    empty_client_session_values.push_back("1");
    empty_client_session_values.push_back("");
    empty_client_session_values.push_back("");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
}

void DB_TEST_BASE::AllocateFullClientSessionVector()
{
    full_client_session_values.push_back("2");                      //Data_id
    full_client_session_values.push_back("2");                      //Client_id
    full_client_session_values.push_back("2");                      //Session_id
    full_client_session_values.push_back("100000000");              //income - QString
    full_client_session_values.push_back("50");                     //feesCharged - QString
    full_client_session_values.push_back("1");                      //feesPaid - TRUE
    full_client_session_values.push_back("1");                      //AttorneyExpected - TRUE
    full_client_session_values.push_back("1");                      //AttorneyAttended - TRUE
    full_client_session_values.push_back("5000");                   //Support - INT
    full_client_session_values.push_back("1");                      //ClientPhone - TRUE
    full_client_session_values.push_back("1");                      //AtTable - TRUE
}

void DB_TEST_BASE::AllocateEmptyNoteValues()
{
    empty_note_values.push_back("1");
    empty_note_values.push_back("0");
    empty_note_values.push_back("0");
    empty_note_values.push_back("Empty Note of Justice.");
    empty_note_values.push_back("2014-07-26 17:23:01");
}

void DB_TEST_BASE::AllocateFullNoteValues()
{
    full_note_values.push_back("2");
    full_note_values.push_back("0");
    full_note_values.push_back("0");
    full_note_values.push_back("This note is going to be filled with wonderfully meaningful, and useful things.");
    full_note_values.push_back("2700-12-31 23:59:59");
}

void DB_TEST_BASE::AllocateEmptyEvaluationVector()
{
    empty_evaluation_values.push_back("1");
    empty_evaluation_values.push_back("2014-07-24 00:00:01");
    empty_evaluation_values.push_back("2014-07-24 00:00:02");
    empty_evaluation_values.push_back("1");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
    empty_evaluation_values.push_back("0");
}

void DB_TEST_BASE::AllocateEmptyUserValues()
{
    empty_user_values.push_back("1");
    empty_user_values.push_back("");
    empty_user_values.push_back("");
    empty_user_values.push_back("");
}
