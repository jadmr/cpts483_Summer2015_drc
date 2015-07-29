#ifndef ALLOCATION_METHODS_H
#define ALLOCATION_METHODS_H

#include <QVector>
#include <QString>

/*
 * Modify the logic of handling AllocateTableNames
 */

QVector< QString > AllocateTableNames()
{
    QVector< QString > table_names;

    table_names.append("Person_Table");
    table_names.append("Mediation_Table");
    table_names.append("Session_Table");
    table_names.append("Client_Table");
    table_names.append("Person_Table");
    table_names.append("Notes_Table");
    table_names.append("Client_session_table");
    table_names.append("User_Table");
    table_names.append("Evaluation_Table");

    return table_names;
}


QVector< QString > AllocatePersonColumns()
{
    QVector< QString > person_table_columns;

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

    return person_table_columns;
}

QVector< QString > AllocateProcessColumns()
{
    QVector< QString > mediation_table_columns;

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

    return mediation_table_columns;
}

QVector< QString > AllocateSessionColumns()
{
    QVector< QString > session_table_columns;

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

    return session_table_columns;
}


QVector< QString > AllocateClientColumns()
{
    QVector< QString > client_table_columns;

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

    return client_table_columns;
}

QVector< QString > AllocateClientSessionColumns()
{
    QVector< QString > client_session_table_columns;

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

    return client_session_table_columns;
}

QVector< QString > AllocateNotesColumns()
{
    QVector< QString > notes_table_columns;

    notes_table_columns.push_back("Note_id");
    notes_table_columns.push_back("Process_id");
    notes_table_columns.push_back("Session_id");
    notes_table_columns.push_back("Note");
    notes_table_columns.push_back("CreateDate");

    return notes_table_columns;
}

QVector< QString > AllocateEvaluationColumns()
{
    QVector< QString > evaluation_table_columns;

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

    return evaluation_table_columns;
}

QVector< QString > AllocateEmptyPersonVector()
{
    QVector< QString > empty_person_values;

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

    return empty_person_values;
}

QVector< QString > AllocateFullPersonVector()
{
    QVector< QString > full_person_values;

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

    return full_person_values;
}

QVector< QString > AllocateEmptyProcessVector()
{
    QVector< QString > empty_process_values;

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

    return empty_process_values;
}

QVector< QString > AllocateFullProcessVector()
{
    QVector< QString > full_process_values;

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

    return full_process_values;
}

QVector< QString > AllocateEmptySessionVector()
{
    QVector< QString > empty_session_values;

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

    return empty_session_values;
}

QVector< QString > AllocateFullSessionVector()
{
    QVector< QString > full_session_values;

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

    return full_session_values;
}

QVector< QString > AllocateEmptyClientVector()
{
    QVector< QString > empty_client_values;

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

    return empty_client_values;
}

QVector< QString > AllocateFullClientVector()
{
    QVector< QString > full_client_values;

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

    return full_client_values;
}

QVector< QString > AllocateEmptyClientSessionVector()
{
    QVector< QString > empty_client_session_values;

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

    return empty_client_session_values;
}

QVector< QString > AllocateFullClientSessionVector()
{
    QVector< QString > full_client_session_values;

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

    return full_client_session_values;
}

QVector< QString > AllocateEmptyNoteValues()
{
    QVector< QString > empty_note_values;

    empty_note_values.push_back("1");
    empty_note_values.push_back("0");
    empty_note_values.push_back("0");
    empty_note_values.push_back("Empty Note of Justice.");
    empty_note_values.push_back("2014-07-26 17:23:01");

    return empty_note_values;
}

QVector< QString > AllocateFullNoteValues()
{
    QVector< QString > full_note_values;

    full_note_values.push_back("2");
    full_note_values.push_back("0");
    full_note_values.push_back("0");
    full_note_values.push_back("This note is going to be filled with wonderfully meaningful, and useful things.");
    full_note_values.push_back("2700-12-31 23:59:59");

    return full_note_values;
}

QVector< QString > AllocateEmptyEvaluationVector()
{
    QVector< QString > empty_evaluation_values;

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

    return empty_evaluation_values;
}

#endif // ALLOCATION_METHODS_H

