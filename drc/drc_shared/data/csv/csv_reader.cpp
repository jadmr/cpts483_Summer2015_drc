#include "csv_reader.h"


CSVReader::CSVReader()
{
    delimiter = ',';
}

CSVReader::CSVReader(QString filepath)
{
    delimiter = ',';

    setFilepath((filepath));
}


QStringList CSVReader::delimitRow(QString row)
{
    QStringList query =  row.split(delimiter);

    return query;
}


QVector<QString> CSVReader::readHeaders()
{
    QVector<QString> headers;
    QFile file(filepath);

    if (file.open(QIODevice::ReadOnly))
    {
        // Read only the first line
       QTextStream in(&file);
       QString line = in.readLine();

       QStringList delimitedHeaders = delimitRow(line);

       for (int count = 0; count < delimitedHeaders.size(); count++)
           headers.append(delimitedHeaders[count]);

       file.close();
    }

    return headers;
}

QVector<QVector<QString> > CSVReader::readRecords()
{
    QVector<QVector<QString> > records;
    QFile file(filepath);

    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
          QVector<QString> row;

          QString line = in.readLine();
          QStringList delimitedRecord = delimitRow(line);

          for (int count = 0; count < delimitedRecord.size(); count++)
              row.append(delimitedRecord[count]);

          records.append(row);
       }

       file.close();
    }

    return records;
}

QVector<QString> CSVReader::readHeaders(QString filepath)
{
    setFilepath(filepath);

    return readHeaders();
}

QVector<QVector<QString> > CSVReader::readRecords(QString filepath)
{
    setFilepath(filepath);

    return readRecords();
}

#define SETTER_GETTER_METHODS {

QString CSVReader::getFilepath() const
{
    return filepath;
}

void CSVReader::setFilepath(const QString &value)
{
    filepath = value;
}

#define SETTER_GETTER_METHODS }
