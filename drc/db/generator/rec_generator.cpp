#include "rec_generator.h"

/*
 * This class generated the indicated number of blah
 */

// Constructor
RecordGenerator::RecordGenerator()
{

}


void RecordGenerator::GenerateRecords(int numMediations)
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

void RecordGenerator::writeToFile(string path, QVector< QVector<QString> > record)
{

}

QVector< QVector<QString> > RecordGenerator::generateClientRecords(int numRecords)
{
    int primaryID = 0;
    QString value;

    QVector< QVector<QString> > clientRecord(numRecords);

    // Initialize matrix to null
    for (int count = 0; count < numRecords; count++)
       clientRecord[count].fill("", value);

    //TODO: query existing databse for metadata, OR use the schema

    return null;
}
