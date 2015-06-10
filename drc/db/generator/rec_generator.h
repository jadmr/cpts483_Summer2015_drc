#ifndef REC_GENERATOR
#define REC_GENERATOR

#include <QString>
#include <QVector>

#include "db_schema.h"
#include "csv_writer.h"

/*
 * Class that generates records from tables in the databse
 * It writes results to a csv file
 */

class RecordGenerator
{

private:

    CSVWriter writer;

    // Helper methods
    QString generateID(int);
    QString generateName(int);
    QString generatePhone(int);
    QString generateAddress(int);
    QString generateState(int);
    QString generateNumber(int);
    QString generateNumber(int, int);
    QString generateDate();
    QString generateTime();
    QString generateBool();
    QString generateIntBool();

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

    void writeToFile(QString, QVector< QVector<QString> >);

public:

    // Constructors
    RecordGenerator();

    void generateRecords(int);
};

#endif // REC_GENERATOR

