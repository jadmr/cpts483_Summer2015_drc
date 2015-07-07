#include "client_session_schema.h"

ClientSessionSchema::ClientSessionSchema() : DatabaseSchema()
{
    setTableName("Client_Session_Table");

    initializeHeaders();
    initializeColumnTypes();
}

void ClientSessionSchema::initializeHeaders()
{
    QVector<QString> clientSessionHeaders;

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

    setHeader(clientSessionHeaders);
}

void ClientSessionSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> clientSessionColumnType;

    clientSessionColumnType.append(PRIMARY_ID);
    clientSessionColumnType.append(SECONDARY_ID);
    clientSessionColumnType.append(SECONDARY_ID);
    clientSessionColumnType.append(DOUBLE);
    clientSessionColumnType.append(INT);
    clientSessionColumnType.append(INT_BOOL);
    clientSessionColumnType.append(INT_BOOL);
    clientSessionColumnType.append(INT_BOOL);
    clientSessionColumnType.append(SUPPORT);
    clientSessionColumnType.append(INT_BOOL);
    clientSessionColumnType.append(INT_BOOL);

    setColumnType(clientSessionColumnType);
}


