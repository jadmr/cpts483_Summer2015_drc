#ifndef DB_SCHEMA
#define DB_SCHEMA

#include <QVector>
#include <QString>

#include "rec_type.h"

/*
 * Class that contains metadata about the database
 * TODO: replace this with sql calls
 */

class DatabaseSchema
{

public:

    DatabaseSchema();

    // Getters
    QVector<QString> getClientHeaders() const;
    QVector<QString> getClientSessionHeaders() const;
    QVector<QString> getEvaluationHeaders() const;
    QVector<QString> getMediationHeaders() const;
    QVector<QString> getNotesHeaders() const;
    QVector<QString> getPersonHeaders() const;
    QVector<QString> getSessionHeaders() const;
    QVector<QString> getUserHeaders() const;

    QVector<RECORD_TYPE> getClientColumnType() const;
    QVector<RECORD_TYPE> getClientSessionColumnType() const;
    QVector<RECORD_TYPE> getEvaluationColumnType() const;
    QVector<RECORD_TYPE> getMediationColumnType() const;
    QVector<RECORD_TYPE> getNotesColumnType() const;
    QVector<RECORD_TYPE> getPersonColumnType() const;
    QVector<RECORD_TYPE> getSessionColumnType() const;
    QVector<RECORD_TYPE> getUserColumnType() const;

private:

    // Column Headers
    QVector<QString> clientHeaders;
    QVector<QString> clientSessionHeaders;
    QVector<QString> evaluationHeaders;
    QVector<QString> mediationHeaders;
    QVector<QString> notesHeaders;
    QVector<QString> personHeaders;
    QVector<QString> sessionHeaders;
    QVector<QString> userHeaders;

    // Column variable types
    QVector<RECORD_TYPE> clientColumnType;
    QVector<RECORD_TYPE> clientSessionColumnType;
    QVector<RECORD_TYPE> evaluationColumnType;
    QVector<RECORD_TYPE> mediationColumnType;
    QVector<RECORD_TYPE> notesColumnType;
    QVector<RECORD_TYPE> personColumnType;
    QVector<RECORD_TYPE> sessionColumnType;
    QVector<RECORD_TYPE> userColumnType;

    // Setters
    void setClientHeaders();
    void setClientSessionHeaders();
    void setEvaluationHeaders();
    void setMediationHeaders();
    void setNotesHeaders();
    void setPersonHeaders();
    void setSessionHeaders();
    void setUserHeaders();

    void setClientColumnType();
    void setClientSessionColumnType();
    void setEvaluationColumnType();
    void setMediationColumnType();
    void setNotesColumnType();
    void setPersonColumnType();
    void setSessionColumnType();
    void setUserColumnType();
};

#endif // DB_SCHEMA
