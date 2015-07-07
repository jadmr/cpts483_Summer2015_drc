#include "client_session_schema.h"

ClientSessionSchema::ClientSessionSchema() : DatabaseSchema()
{
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

    setColumnType(clientSessionColumnType);
}


