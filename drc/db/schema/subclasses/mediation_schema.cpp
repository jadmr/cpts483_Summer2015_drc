#include "mediation_schema.h"


MediationSchema::MediationSchema() : DatabaseSchema()
{
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

    setHeader(mediationHeaders);
}

void MediationSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> mediationColumnType;

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
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);
    mediationColumnType.append(INT);

    setColumnType(mediationColumnType);
}

#define OVERRIDES_OF_BASE }
