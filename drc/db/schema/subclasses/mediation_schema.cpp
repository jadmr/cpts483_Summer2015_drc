#include "mediation_schema.h"


MediationSchema::MediationSchema() : DatabaseSchema()
{
    setTableName("Mediation_Table");

    initializeHeaders();
    initializeColumnTypes();
}

#define OVERRIDES_OF_BASE {

void MediationSchema::initializeHeaders()
{
    QVector<QString> mediationHeaders;

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
    mediationHeaders.append("IndirectChildren");
    mediationHeaders.append("DirectChildren");
    mediationHeaders.append("IndirectAdult");
    mediationHeaders.append("DirectAdult");
    mediationHeaders.append("ShorthandNotes");

    setHeader(mediationHeaders);
}

void MediationSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> mediationColumnType;

    mediationColumnType.append(PRIMARY_ID);
    mediationColumnType.append(DISPUTE_TYPE);
    mediationColumnType.append(LOWER_DATE);
    mediationColumnType.append(MIDDLE_DATE);
    mediationColumnType.append(LOWER_DATETIME);
    mediationColumnType.append(MIDDLE_DATETIME);
    mediationColumnType.append(DISPUTE_STATE);
    mediationColumnType.append(DISPUTE_INTERNAL_STATE);
    mediationColumnType.append(COUNTY);
    mediationColumnType.append(REFERRAL_SOURCE);
    mediationColumnType.append(INQUIRY_TYPE);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(UPPER_DATE);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(STRING);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(INT_BOOL);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);

    setColumnType(mediationColumnType);
}

#define OVERRIDES_OF_BASE }
