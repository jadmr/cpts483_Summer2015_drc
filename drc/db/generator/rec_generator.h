#ifndef REC_GENERATOR
#define REC_GENERATOR

#include "csv_writer.h"

/*
 * Class that generates records from tables in the databse
 * It writes results to a csv file
 */

class RecordGenerator
{

private:

    CSVWriter writer;

    //TODO: This enum probably belongs in the schema
    enum class RECORD_TYPE { ID,
                             FIRST_NAME,
                             LAST_NAME,
                             PHONE_NUMBER,
                             EMAIL,
                             ADDRESS,
                             CITY,
                             STATE,
                             ZIP,
                             DATE,
                             DATE_TIME,
                             STRING,
                             DOUBLE,
                             INT};

    // Helper methods
    QString generateRecordValue(int, RECORD_TYPE);
    int getRandomNumber(int, int);

    // Method to generate records
    QVector< QVector<QString> > generateClientRecords(int);
    QVector< QVector<QString> > generateClientSessionRecords(int);
    QVector< QVector<QString> > generateEvaluationRecords(int);
    QVector< QVector<QString> > generateMediationRecords(int);
    QVector< QVector<QString> > generateNotesRecords(int);
    QVector< QVector<QString> > generatePersonRecords(int);
    QVector< QVector<QString> > generateSessionRecords(int);
    QVector< QVector<QString> > generateUserRecords(int);

    void writeToFile(string, QVector< QVector<QString> >);

public:

    // Constructors
    RecordGenerator();

    void generateRecords(int);
};

#endif // REC_GENERATOR

