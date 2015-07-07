#include "csv_writer.h"

CSVWriter::CSVWriter()
{
    delimiter = ",";
}

void CSVWriter::writeRecordsToFile(QString filename, QVector<QString> headers, QVector< QVector<QString> > records)
{
    QFile file(filename);

    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);

        writeHeaders(headers, stream);
        writeRecords(records, stream);
    }

    file.close();
}

void CSVWriter::writeHeaders(QVector<QString> headers, QTextStream &stream)
{
    auto size = headers.size() - 1; // do not write the last element

    for (int count = 0; count < size; count++)
        stream << headers[count] << delimiter;

    stream << headers.back() << endl;
}

void CSVWriter::writeRecords(QVector< QVector<QString> > records, QTextStream &stream)
{
    int rowSize = records.size();
    int columnSize = records[0].size();

    for (int row = 0; row < rowSize; row++)
    {
        for (int column = 0; column < (columnSize - 1); column++)
            stream << records[row][column] << delimiter;

        stream << records[row].back() << endl;
    }
}






