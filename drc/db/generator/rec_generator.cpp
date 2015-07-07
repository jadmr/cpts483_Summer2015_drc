#include "rec_generator.h"

/*
 * This class generates the indicated number of blah
 */

// Constructor
RecordGenerator::RecordGenerator()
{
    // Table Schemas
    ClientSchema* clientSchema = new ClientSchema();
    ClientSessionSchema* clientSessionSchema = new ClientSessionSchema();
    EvaluationSchema* evaluationSchema = new EvaluationSchema();
    MediationSchema* mediationSchema = new MediationSchema();
    NotesSchema* notesSchema = new NotesSchema();
    PersonSchema* personSchema = new PersonSchema();
    SessionSchema* sessionSchema = new SessionSchema();
    UserSchema* userSchema = new UserSchema();

    schemas.append(mediationSchema);
    schemas.append(sessionSchema);
    schemas.append(personSchema);
    schemas.append(clientSchema);
    schemas.append(clientSessionSchema);
    schemas.append(evaluationSchema);
    schemas.append(notesSchema);
    schemas.append(userSchema);

    // Initialize id table
    for (int count = 0; count < schemas.size(); count++)
    {
        // Problem is the hedaers, it returns a vector instead of a string
        // Primary id is always first column. What about 2nd keys? Dont
        // worry about cols other than 1st (primary key), theyll appear later
        // if needed as the first columns

        QStringList list;
        auto primaryID = schemas[count]->getPrimaryID();

        idTable.insert(primaryID, list); //TODO: check pointers of parameters
    }
}

// Destructor
RecordGenerator::~RecordGenerator()
{
    //TODO: Convert to while loop
    int size = schemas.size();

    for (int count = 0; count < size; count++)
    {
        delete schemas[count];
    }

    // TODO: Free the lists in the id table as well
}


void RecordGenerator::generateRecords(int numMediations)
{
    //TODO: dont want numMediations of everything

    // Generate tables
    int size = schemas.size();

    for (int count = 0; count <  size; count++)
    {
        QVector< QVector<QString> > record = generateTable(numMediations, schemas.at(count));

        // Write results to a table file
        writer.writeRecordsToFile(schemas[count]->getTableName(),
                                  schemas[count]->getHeader(),
                                  record);
    }
}

#define TABLE_GENERATION_METHODS {

QVector<QVector<QString> > RecordGenerator::generateTable(int numRecords, DatabaseSchema* schema)
{
    QString value;

    int rows = numRecords + 1;
    int cols = schema->getHeader().count();
    int seed = 0;

    QVector< QVector<QString> > records(numRecords);

    // Populate matrix
    for (int currentRow = 0; currentRow < rows; currentRow++)
    {
        for (int currentColumn = 0; currentColumn < cols; currentColumn++)
        {
            ++seed;

            value = generateRecord(schema->getColumnType().at(currentColumn), schema->getHeader().at(currentColumn), seed);
            records[currentRow][currentColumn] = value;
        }
    }

    return records;
}

#define TABLE_GENERATION_METHODS }

#define RANDOM_NUMBER_GENERATOR_METHODS {

int RecordGenerator::getRandomNumber(int lowerLimit, int upperLimit)
{
    return (qrand() % ((upperLimit + 1) - lowerLimit) + lowerLimit);
}

#define RANDOM_NUMBER_GENERATOR_METHODS }

#define VARIABLE_GENERATION_METHODS {
QString RecordGenerator::generateRecord(RECORD_TYPE recordType, QString columnHeader, int seed)
{
    QString value;

    switch (recordType)
    {
        case PRIMARY_ID:
        value = generateID(columnHeader, recordType, seed);
        break;

        case SECONDARY_ID:
        value = generateID(columnHeader, recordType, seed);
        break;

        case FIRST_NAME:
        value = generateString("First_Name", seed);
        break;

        case MIDDLE_NAME:
        value = generateString("Middle_Name", seed);
        break;

        case LAST_NAME:
        value = generateString("Last_Name", seed);
        break;

        case PHONE_NUMBER:
        value = generatePhoneNumber();
        break;

        case PHONE_EXT:
        value = generateNumOfInts(3, 1, 9);
        break;

        case EMAIL:
        value = generateEmail(seed);
        break;

        case ADDRESS:
        value = generateAddress(seed);
        break;

        case CITY:
        value = generateCity();
        break;

        case COUNTY:
        value = generateInt(1, 3);
        break;

        case STATE:
        value = generateString("WA");
        break;

        case UPPER_DATE:
        value = generateDate("upper");
        lastDate = value;
        break;

        case MIDDLE_DATE:
        value = generateDate("middle");
        lastDate = value;
        break;

        case LOWER_DATE:
        value = generateDate("lower");
        lastDate = value;
        break;

        case UPPER_DATETIME:
        value = lastDate + " " + generateTime();
        break;

        case MIDDLE_DATETIME:
        value = lastDate + " " + generateTime();
        break;

        case LOWER_DATETIME:
        value = lastDate + " " + generateTime();
        break;

        case NEW_UPPER_DATETIME:
        value = generateDate("upper") + " " + generateTime();
        break;

        case NEW_MIDDLE_DATETIME:
        value = generateDate("middle") + " " + generateTime();
        break;

        case NEW_LOWER_DATETIME:
        value = generateDate("lower") + " " + generateTime();
        break;

        case STRING:
        value = generateString("Random_String_", seed);
        break;

        case INT_BOOL:
        value = generateInt(0, 1);
        break;

        case BOOL:
        value = generateBool();
        break;

        case DOUBLE:
        value = generateDouble();
        break;

        case INT:
        value =  generateInt(0, 25);
        break;

        case EVALUATION_SCORE:
        value = generateInt(0, 10);
        break;

        case SUPPORT:
        value = generateInt(0, 2);
        break;

        case DISPUTE_TYPE:
        value = generateInt(1, 14);
        break;

        case DISPUTE_STATE:
        value = generateInt(1, 4);
        break;

        case DISPUTE_INTERNAL_STATE:
        value = generateInt(1, 10);
        break;

        case REFERRAL_SOURCE:
        value = generateInt(1, 16);
        break;

        case INQUIRY_TYPE:
        value = generateInt(1, 4);
        break;

        case COUNTY_NAME:
        value = generateInt(1, 6);
        break;

        case SESSION_STATUS:
        value = generateInt(1, 4);
        break;

        case SESSION_OUTCOME:
        value = generateInt(0, 9);
        break;

        case USER_NAME:
        value = generateString("Admin");
        break;

        case PASSWORD:
        value = generateString("8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918");
        break;

        case ADMIN_BOOL:
        value = generateString("true");
        break;

        default:
        break;
    }

    return value;
}

// Returns a random value (no range)
QString RecordGenerator::generateInt()
{
    return QString::number(getRandomNumber(1, 100));
}

// Returns the seed + 1
QString RecordGenerator::generateInt(int seed)
{
    return QString::number(seed + 1);
}

// Returns a number within the given range
QString RecordGenerator::generateInt(int lowerBound, int upperBound)
{
    return QString::number(getRandomNumber(lowerBound, upperBound));
}

// Return the specified number of ints (ie, for phone ext)
QString RecordGenerator::generateNumOfInts(int seed)
{
    QString value;

    for (int count = 0; count < seed; count++)
        value += QString::number(getRandomNumber(1, 100));

    return value;
}

// Return the specified number of ints, with a range
QString RecordGenerator::generateNumOfInts(int seed, int lowerBound, int upperBound)
{
    QString value;

    for (int count = 0; count < seed; count++)
        value += QString::number(getRandomNumber(lowerBound, upperBound));

    return value;
}

// Return a random fraction (ie, money)
QString RecordGenerator::generateDouble()
{
    int beforeDecimal = getRandomNumber(1, 100);
    int afterDecimal = getRandomNumber(0, 99);

    return QString::number(beforeDecimal) + "." + QString::number(afterDecimal);
}

// Return ... the same string
QString RecordGenerator::generateString(QString value)
{
    return value;
}

// Return the string + the seed
QString RecordGenerator::generateString(QString value, int seed)
{
    return value + QString::number(seed);
}

// Return a random bool
QString RecordGenerator::generateBool()
{
    if (getRandomNumber(0, 1) == 0)
        return "False";
    else
        return "True";
}

// Return a *valid* id
QString RecordGenerator::generateID(QString columnHeader, RECORD_TYPE recordType, int seed)
{
    QString value;

    // Get the relevant list
    auto list = idTable.value(columnHeader);

    // Check the map of IDs
    if (recordType == PRIMARY_ID)
    {
        // Use the seed as the new ID
        list.append(QString::number(seed));

        idTable.insert(columnHeader, list);
        value = QString::number(seed);
    }
    else if (recordType == SECONDARY_ID)
    {
        // Pick an existing ID
        int size = list.size();
        int index = getRandomNumber(0, size);

        value = list[index];
    }

    return value;
}

// Return a valid phone number
QString RecordGenerator::generatePhoneNumber()
{
    QString areaCode = generateNumOfInts(3, 1, 9);
    QString centralOfficeCode = generateNumOfInts(3, 0, 9);
    QString stationNumber = generateNumOfInts(4, 0, 9);

    return areaCode + "-" + centralOfficeCode + "-" + stationNumber;
}

// Return a street address
QString RecordGenerator::generateAddress(int seed)
{
    QStringList streetType = (QStringList() << "Ave" << "St" << "Ln" << "Ct");

    QString houseNumber = generateNumOfInts(3, 1, 9);
    QString streetName = "LinuxRocks" + QString::number(seed);
    QString type = streetType.at(getRandomNumber(0, 3));

    return houseNumber + " " + streetName + " " + type;
}

// Return a city
QString RecordGenerator::generateCity()
{
    QStringList city = (QStringList() << "Pasco" << "Kennewick" << "Richland");

    return city.at(getRandomNumber(0, 2));
}

// Return an email
QString RecordGenerator::generateEmail(int seed)
{
    return "generic_email_" + QString::number(seed) + "@host.com";
}

// Return a random date within the specified range
QString RecordGenerator::generateDate(QString type)
{
    //TODO: easiest to accept date in days (1-365) and convert to string
    // For now, make this simple (All 2014)

    QString year = "2014-";
    QString day = QString::number(getRandomNumber(1, 28));
    QString month;

    if (QString::compare(type, "lower", Qt::CaseInsensitive) == 0)
    {
        // Reserve Jan - April for start dates
        month = QString::number(getRandomNumber(1, 5));
    }
    else if (QString::compare(type, "middle", Qt::CaseInsensitive) == 0)
    {
        // Reserve May - August for mid dates
        month = QString::number(getRandomNumber(5, 8));
    }
    else
    {
        // Reserve September - December for end dates
        month = QString::number(getRandomNumber(9, 12));
    }

    return year + month + "-" + day;
}

// Returns a time in
QString RecordGenerator::generateTime()
{
    return "12:00:00"; // More trouble than its worth
}


#define VARIABLE_GENERATION_METHODS }


