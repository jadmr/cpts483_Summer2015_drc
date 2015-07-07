#include "person_schema.h"


PersonSchema::PersonSchema() : DatabaseSchema()
{
    setTableName("Person_Table");

    initializeHeaders();
    initializeColumnTypes();
}

#define OVERRIDES_OF_BASE {

void PersonSchema::initializeHeaders()
{
    QVector<QString> personHeaders;

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

    setHeader(personHeaders);
}

void PersonSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> personColumnType;

    personColumnType.append(PRIMARY_ID);
    personColumnType.append(FIRST_NAME);
    personColumnType.append(MIDDLE_NAME);
    personColumnType.append(LAST_NAME);
    personColumnType.append(ADDRESS);
    personColumnType.append(STRING);
    personColumnType.append(CITY);
    personColumnType.append(STATE);
    personColumnType.append(INT);
    personColumnType.append(COUNTY_NAME);
    personColumnType.append(PHONE_NUMBER);
    personColumnType.append(PHONE_EXT);
    personColumnType.append(PHONE_NUMBER);
    personColumnType.append(PHONE_EXT);
    personColumnType.append(EMAIL);

    setColumnType(personColumnType);
}

#define OVERRIDES_OF_BASE }
