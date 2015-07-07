#include "session_schema.h"


SessionSchema::SessionSchema() : DatabaseSchema()
{
    setTableName("Session_Table");

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

    sessionColumnType.append(PRIMARY_ID);
    sessionColumnType.append(SECONDARY_ID);
    sessionColumnType.append(SESSION_STATUS);
    sessionColumnType.append(SESSION_OUTCOME);
    sessionColumnType.append(NEW_MIDDLE_DATETIME);
    sessionColumnType.append(NEW_MIDDLE_DATETIME);
    sessionColumnType.append(NEW_UPPER_DATETIME);
    sessionColumnType.append(FIRST_NAME);
    sessionColumnType.append(FIRST_NAME);
    sessionColumnType.append(FIRST_NAME);
    sessionColumnType.append(FIRST_NAME);
    sessionColumnType.append(INT_BOOL);

    setColumnType(sessionColumnType);
}

#define OVERRIDES_OF_BASE }
