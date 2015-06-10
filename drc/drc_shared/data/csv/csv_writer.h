#ifndef CSV_WRITER
#define CSV_WRITER

#include <QString>
#include <QVector>

/*
 * Class that writes database records to a file
 */

class CSVWriter{
private:
public:
    CSVWriter();

    void writeRecord(QVector<QString>, QVector< QVector<QString> >);
};

#endif // CSV_WRITER

