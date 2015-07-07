#ifndef CSV_WRITER
#define CSV_WRITER

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>

/*
 * Class that writes database records to a file
 */

class CSVWriter
{
private:

    QString delimiter;

    void writeHeaders(QVector<QString>, QTextStream&);
    void writeRecords(QVector< QVector<QString> >, QTextStream&);

public:
    CSVWriter();

    void writeRecordsToFile(QString, QVector<QString>, QVector< QVector<QString> >);
};

#endif // CSV_WRITER

