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
            //schema.getClientColumnType().at(currentColumn);

     //       if (schema.getClientColumnType().at(currentColumn) == schema::ID)
     //           clientRecord[currentRow][currentColumn] = generateID(currentRow + 1);

        }
    }

    return clientRecord;
}

QString RecordGenerator::generateID(int seed)
{
    QString id = QString::number(seed);

    return id;
}

QString RecordGenerator::generateName(int seed)
{

}

QString RecordGenerator::generatePhone(int seed)
{

}

QString RecordGenerator::generateAddress(int seed)
{

}

QString RecordGenerator::generateState(int seed)
{

}

QString RecordGenerator::generateNumber(int seed)
{

}

QString RecordGenerator::generateNumber(int lowerBound, int upperBound)
{

}

QString generateDate()
{

}

QString generateTime()
{

}

QString RecordGenerator::generateBool()
{

}

QString RecordGenerator::generateIntBool()
{

}
