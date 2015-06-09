#ifndef CSV_WRITER
#define CSV_WRITER

/*
 * Class that writes database records to a file
 */

class CSVWriter{
private:
public:
    CSVWriter();

    void writeRecord(QVector<Qstring> header, QVector< QVector<QString> > records);
};

#endif // CSV_WRITER

