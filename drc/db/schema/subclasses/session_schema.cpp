#include "session_schema.h"


SessionSchema::SessionSchema() : DatabaseSchema()
{
    initializeHeaders();
    initializeColumnTypes();
}

#define OVERRIDES_OF_BASE {

void SessionSchema::initializeHeaders()
{
    QVector<QString> sessionHeaders;

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

    setHeader(sessionHeaders);
}

void SessionSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> sessionColumnType;

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

    setColumnType(sessionColumnType);
}

#define OVERRIDES_OF_BASE }
