#include "rec_generator.h"

/*
 * This class generated the indicated number of blah
 */

// Constructor
RecordGenerator::RecordGenerator()
{

}

void RecordGenerator::generateRecords(int numMediations)
{
    //TODO: dont want numMediations of everything

    // Generate Client Records
    QVector< QVector<QString> > clientRecord = generateClientRecords(numMediations);

    // Generate Client Session Records
    QVector< QVector<QString> > clientSessionRecord = generateClientRecords(numMediations);

    // Generate Evaluation Records
    QVector< QVector<QString> > evaluationRecord = generateClientRecords(numMediations);

    // Generate Mediation Records
    QVector< QVector<QString> > mediationRecord = generateClientRecords(numMediations);

    // Generate Notes Records
    QVector< QVector<QString> > notesRecord = generateClientRecords(numMediations);

    // Generate Person Records
    QVector< QVector<QString> > personRecord = generateClientRecords(numMediations);

    // Generate Session Records
    QVector< QVector<QString> > sessionRecord = generateClientRecords(numMediations);

    // Generate User Records
    QVector< QVector<QString> > userRecord = generateClientRecords(numMediations);
}

void RecordGenerator::writeToFile(QString path, QVector< QVector<QString> > record)
{

}

QVector< QVector<QString> > RecordGenerator::generateClientRecords(int numRecords)
{
    DatabaseSchema schema;
    QString value;

    int rows = numRecords + 1;
    int cols = schema.getClientHeaders().count();

    QVector< QVector<QString> > clientRecord(numRecords);

    // Populate matrix
    for (int currentRow = 0; currentRow < rows; currentRow++)
    {
        for (int currentColumn = 0; currentColumn < cols; currentColumn++)
        {
            value = generateRecord(schema.getClientColumnType().at(currentColumn));
            clientRecord[currentRow][currentColumn] = value;
        }
    }

    return clientRecord;
}

QString RecordGenerator::generateRecord(RECORD_TYPE recordType)
{
    QString value;

    switch (recordType)
    {
        case ID:
        break;

        case FIRST_NAME:
        break;

        case MIDDLE_NAME:
        break;

        case LAST_NAME:
        break;

        case PHONE_NUMBER:
        break;

        case PHONE_EXT:
        break;

        case EMAIL:
        break;

        case ADDRESS:
        break;

        case CITY:
        break;

        case STATE:
        break;

        case UPPER_DATE:
        break;

        case LOWER_DATE:
        break;

        case UPPER_DATETIME:
        break;

        case LOWER_DATETIME:
        break;

        case INT_BOOL:
        break;

        case BOOL:
        break;

        case INT_WITH_RANGE:
        break;

        default:
        break;
    }

    return value;
}

// Returns a random value (no range)
QString RecordGenerator::generateInt()
{

}

// Returns the parameter + 1
QString RecordGenerator::generateInt(int seed)
{

}

// returns a number within the given range
QString RecordGenerator::generateInt(int, int)
{

}

// return the specified number of ints (ie, for phone ext)
QString RecordGenerator::genereateNumOfInts(int)
{

}




