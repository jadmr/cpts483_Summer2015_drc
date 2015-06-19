#include "db_schema.h"

// Constructor
DatabaseSchema::DatabaseSchema()
{
    setClientHeaders();
    setClientSessionHeaders();
    setEvaluationHeaders();
    setMediationHeaders();
    setNotesHeaders();
    setPersonHeaders();
    setSessionHeaders();
    setUserHeaders();

    setClientColumnType();
    setClientSessionColumnType();
    setEvaluationColumnType();
    setMediationColumnType();
    setNotesColumnType();
    setPersonColumnType();
    setSessionColumnType();
    setUserColumnType();
}


// Setters and Getters

QVector<QString> DatabaseSchema::getClientHeaders() const
{
    return clientHeaders;
}

void DatabaseSchema::setClientHeaders()
{
    clientHeaders.append("Client_id");
    clientHeaders.append("Process_id");
    clientHeaders.append("Person_id");
    clientHeaders.append("Children");
    clientHeaders.append("Adult");
    clientHeaders.append("AttorneyName");
    clientHeaders.append("AttorneyPhone");
    clientHeaders.append("AttorneyEmail");
    clientHeaders.append("AssistantName");
    clientHeaders.append("AssistantPhone");
    clientHeaders.append("AssistantEmail");
}

QVector<QString> DatabaseSchema::getClientSessionHeaders() const
{
    return clientSessionHeaders;
}

void DatabaseSchema::setClientSessionHeaders()
{
    clientSessionHeaders.append("Data_id");
    clientSessionHeaders.append("Client_id");
    clientSessionHeaders.append("Session_id");
    clientSessionHeaders.append("income");
    clientSessionHeaders.append("feesCharged");
    clientSessionHeaders.append("feesPaid");
    clientSessionHeaders.append("AttorneyExpected");
    clientSessionHeaders.append("AttorneyAttended");
    clientSessionHeaders.append("Support");
    clientSessionHeaders.append("ClientPhone");
    clientSessionHeaders.append("AtTable");
}

QVector<QString> DatabaseSchema::getEvaluationHeaders() const
{
    return evaluationHeaders;
}

void DatabaseSchema::setEvaluationHeaders()
{
    evaluationHeaders.append("Id");
    evaluationHeaders.append("startDate");
    evaluationHeaders.append("endDate");
    evaluationHeaders.append("CountIdd");
    evaluationHeaders.append("FairYes");
    evaluationHeaders.append("FairNo");
    evaluationHeaders.append("FairSomewhat");
    evaluationHeaders.append("ImproveYes");
    evaluationHeaders.append("ImproveNo");
    evaluationHeaders.append("ImroveSomewhat");
    evaluationHeaders.append("CommunicateYes");
    evaluationHeaders.append("CommunicateNo");
    evaluationHeaders.append("CommunicateSomewhat");
    evaluationHeaders.append("UnderstandYes");
    evaluationHeaders.append("UnderstandNo");
    evaluationHeaders.append("UnderstandSomewhat");
    evaluationHeaders.append("RecommendYes");
    evaluationHeaders.append("RecommendNo");
    evaluationHeaders.append("RecommendSomewhat");
    evaluationHeaders.append("AgreementYes");
    evaluationHeaders.append("AgreementNo");
    evaluationHeaders.append("AgreementSomewhat");
}

QVector<QString> DatabaseSchema::getMediationHeaders() const
{
    return mediationHeaders;
}

void DatabaseSchema::setMediationHeaders()
{
    mediationHeaders.append("Process_id");
    mediationHeaders.append("DisputeType");
    mediationHeaders.append("CreationDate");
    mediationHeaders.append("UpdatedDate");
    mediationHeaders.append("CreationDateTime");
    mediationHeaders.append("UpdatedDateTime");
    mediationHeaders.append("DisputeDate");
    mediationHeaders.append("DisputeInternalState");
    mediationHeaders.append("DisputeCounty");
    mediationHeaders.append("ReferalSource");
    mediationHeaders.append("InquiryType");
    mediationHeaders.append("InfoOnly");
    mediationHeaders.append("IsCourtCase");
    mediationHeaders.append("CourtDate");
    mediationHeaders.append("CourtCaseType");
    mediationHeaders.append("CourtOrderType");
    mediationHeaders.append("TranslatorRequired");
    mediationHeaders.append("SessionType");
    mediationHeaders.append("MediationClause");
}

QVector<QString> DatabaseSchema::getNotesHeaders() const
{
    return notesHeaders;
}

void DatabaseSchema::setNotesHeaders()
{
    notesHeaders.append("Note_id");
    notesHeaders.append("Process_id");
    notesHeaders.append("Session_id");
    notesHeaders.append("Note");
    notesHeaders.append("CreateDate");
}

QVector<QString> DatabaseSchema::getPersonHeaders() const
{
    return personHeaders;
}

void DatabaseSchema::setPersonHeaders()
{
    personHeaders.append("Person_id");
    personHeaders.append("first_name");
    personHeaders.append("middle_name");
    personHeaders.append("last_name");
    personHeaders.append("street_name");
    personHeaders.append("unit_name");
    personHeaders.append("city_name");
    personHeaders.append("state_name");
    personHeaders.append("zip_code");
    personHeaders.append("county_name");
    personHeaders.append("primary_phone");
    personHeaders.append("primary_phone_ext");
    personHeaders.append("secondary_phone");
    personHeaders.append("secondary_pphone_ext");
    personHeaders.append("email_address");

}

QVector<QString> DatabaseSchema::getSessionHeaders() const
{
    return sessionHeaders;
}

void DatabaseSchema::setSessionHeaders()
{
    sessionHeaders.append("Session_id");
    sessionHeaders.append("Process_id");
    sessionHeaders.append("SessionStatus");
    sessionHeaders.append("SessionOutcome");
    sessionHeaders.append("CreatedDateTime");
    sessionHeaders.append("UpdatedDateTime");
    sessionHeaders.append("ScheduledDateTime");
    sessionHeaders.append("Mediator1");
    sessionHeaders.append("Mediator2");
    sessionHeaders.append("Observer1");
    sessionHeaders.append("Observer2");
    sessionHeaders.append("Shuttle");
}

QVector<QString> DatabaseSchema::getUserHeaders() const
{
    return userHeaders;
}

void DatabaseSchema::setUserHeaders()
{
    userHeaders.append("user_id");
    userHeaders.append("user_name");
    userHeaders.append("user_password");
    userHeaders.append("Admin");

}

QVector<RECORD_TYPE> DatabaseSchema::getClientColumnType() const
{
    return clientColumnType;
}

void DatabaseSchema::setClientColumnType()
{
    clientColumnType.append(ID);
    clientColumnType.append(INT);
    clientColumnType.append(INT);
    clientColumnType.append(INT);
    clientColumnType.append(INT);
    clientColumnType.append(FIRST_NAME);
    clientColumnType.append(PHONE_NUMBER);
    clientColumnType.append(EMAIL);
    clientColumnType.append(FIRST_NAME);
    clientColumnType.append(PHONE_NUMBER);
    clientColumnType.append(EMAIL);
}

QVector<RECORD_TYPE> DatabaseSchema::getClientSessionColumnType() const
{
    return clientSessionColumnType;
}

void DatabaseSchema::setClientSessionColumnType()
{
    clientSessionColumnType.append(ID);
    clientSessionColumnType.append(ID);
    clientSessionColumnType.append(ID);
    clientSessionColumnType.append(INT);
    clientSessionColumnType.append(INT);
    clientSessionColumnType.append(INT);
    clientSessionColumnType.append(INT);
    clientSessionColumnType.append(INT);
    clientSessionColumnType.append(INT);
    clientSessionColumnType.append(INT);
    clientSessionColumnType.append(INT);
}

QVector<RECORD_TYPE> DatabaseSchema::getEvaluationColumnType() const
{
    return evaluationColumnType;
}

void DatabaseSchema::setEvaluationColumnType()
{
    evaluationColumnType.append(ID);
    evaluationColumnType.append(DATE);
    evaluationColumnType.append(DATE);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
    evaluationColumnType.append(INT);
}

QVector<RECORD_TYPE> DatabaseSchema::getMediationColumnType() const
{
    return mediationColumnType;
}

void DatabaseSchema::setMediationColumnType()
{
    mediationColumnType.append(ID);
    mediationColumnType.append(ID);
    mediationColumnType.append(DATE);
    mediationColumnType.append(DATE);
    mediationColumnType.append(DATE_TIME);
    mediationColumnType.append(DATE_TIME);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(DATE);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(STRING);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(INT_BOOL);
}

QVector<RECORD_TYPE> DatabaseSchema::getNotesColumnType() const
{
    return notesColumnType;
}

void DatabaseSchema::setNotesColumnType()
{
    notesColumnType.append(ID);
    notesColumnType.append(ID);
    notesColumnType.append(ID);
    notesColumnType.append(STRING);
    notesColumnType.append(DATE_TIME);
}

QVector<RECORD_TYPE> DatabaseSchema::getPersonColumnType() const
{
    return personColumnType;
}

void DatabaseSchema::setPersonColumnType()
{
    personColumnType.append(ID);
    personColumnType.append(FIRST_NAME);
    personColumnType.append(FIRST_NAME);
    personColumnType.append(LAST_NAME);
    personColumnType.append(ADDRESS);
    personColumnType.append(STRING);
    personColumnType.append(CITY);
    personColumnType.append(STATE);
    personColumnType.append(INT);
    personColumnType.append(INT);
    personColumnType.append(PHONE_NUMBER);
    personColumnType.append(INT);
    personColumnType.append(PHONE_NUMBER);
    personColumnType.append(INT);
    personColumnType.append(EMAIL);
}

QVector<RECORD_TYPE> DatabaseSchema::getSessionColumnType() const
{
    return sessionColumnType;
}

void DatabaseSchema::setSessionColumnType()
{
    sessionColumnType.append(ID);
    sessionColumnType.append(ID);
    sessionColumnType.append(INT);
    sessionColumnType.append(INT);
    sessionColumnType.append(DATE_TIME);
    sessionColumnType.append(DATE);
    sessionColumnType.append(DATE_TIME);
    sessionColumnType.append(FIRST_NAME);
    sessionColumnType.append(FIRST_NAME);
    sessionColumnType.append(FIRST_NAME);
    sessionColumnType.append(FIRST_NAME);
    sessionColumnType.append(INT_BOOL);
}

QVector<RECORD_TYPE> DatabaseSchema::getUserColumnType() const
{
    return userColumnType;
}

void DatabaseSchema::setUserColumnType()
{
    userColumnType.append(ID);
    userColumnType.append(STRING);
    userColumnType.append(STRING);
    userColumnType.append(BOOL);
}

