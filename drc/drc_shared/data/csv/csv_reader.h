#ifndef CSV_READER
#define CSV_READER

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QStringList>

class CSVReader
{
private:
    QString filepath;
    QString delimiter;

    QStringList delimitRow(QString);
public:

        CSVReader();
        CSVReader(QString);

        QVector<QString> readHeaders();
        QVector< QVector<QString> > readRecords();

        QVector<QString> readHeaders(QString);
        QVector< QVector<QString> > readRecords(QString);

#define GETTER_SETTER_METHODS {

        QString getFilepath() const;
        void setFilepath(const QString &value);

#define GETTER_SETTER_METHODS }
};

#endif // CSV_READER

