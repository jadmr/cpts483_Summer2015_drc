#include "client_schema.h"

ClientSchema::ClientSchema() : DatabaseSchema()
{
    initializeHeaders();
    initializeColumnTypes();
}

#define OVERRIDES_OF_BASE {

void ClientSchema::initializeHeaders()
{
    QVector<QString> clientHeaders;

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

    setHeader(clientHeaders);
}

void ClientSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> clientColumnType;

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

    setColumnType(clientColumnType);
}

#define OVERRIDES_OF_BASE }
