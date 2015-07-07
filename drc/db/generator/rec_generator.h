#ifndef REC_GENERATOR
#define REC_GENERATOR

#include <QString>
#include <QVector>
#include <QStringList>

#include "db_schema.h"
#include "client_schema.h"
#include "client_session_schema.h"
#include "evaluation_schema.h"
#include "mediation_schema.h"
#include "notes_schema.h"
#include "person_schema.h"
#include "session_schema.h"
#include "user_schema.h"

#include "csv_writer.h"
#include "rec_type.h"

/*
 * Class that generates records from tables in the databse
 * It writes results to a csv file
 *
 * TODO: Create a dictionary that stores (id, date) to make dates consistent
 * Make it a part of the class so *everyone* can see and use it
 *
 * For the random int ranges, maybe pass the column name to the method
 * Depending on which column it is, generate within the appropriate range (1-4, 1-9, etc)
 */

class RecordGenerator
{

private:

#define PRIVATE_VARIABLES {
    CSVWriter writer;
#define PRIVATE_VARIABLES }

#define VARIABLE_GENERATION_METHODS {
    QString generateRecord(RECORD_TYPE, int);

    QString generateInt();
    QString generateInt(int);
    QString generateInt(int, int);    // useful for county (1-3)
    QString generateNumOfInts(int);  // specify how many numbers you want
    QString generateNumOfInts(int, int, int); // with range
    QString generateDouble();
    QString generateString(QString);
    QString generateString(QString, int);
    QString generateBool();

    // Not so easy
    QString generatePhoneNumber();
    QString generateAddress(int);
    QString generateCity();
    QString generateEmail(int);
    QString generateDate(QString);
    QString generateTime(); // REALLY tricky (for DateTime)

    //TODO: Login Credentials

#define VARIABLE_GENERATION_METHODS }

#define TABLE_GENERATION_METHODS {

    QVector< QVector<QString> > generateTable(int, DatabaseSchema* schema);

#define TABLE_GENERATION_METHODS }

#define RANDOM_NUMBER_GENERATOR_METHODS {
    int getRandomNumber(int, int);
#define RANDOM_NUMBER_GENERATOR_METHODS }

#define FILE_IO_METHODS {
    void writeToFile(QString, QVector< QVector<QString> >);
#define FILE_IO_METHODS }

public:

    // Constructors
    RecordGenerator();

    void generateRecords(int);
};

#endif // REC_GENERATOR

