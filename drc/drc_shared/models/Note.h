#ifndef NOTEFORM_H
#define NOTEFORM_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <QTextCursor>

#include "DBBaseObject.h"

class Note : public DBBaseObject
{
private:
    QString _message;
    int _sessionId;
    int _mediationId;
public:
    Note(QString message = "");
    void SetMessage(QString message);
    void SetSessionId(int sessionId);
    void SetMediationId(int mediationId);

    QString GetMessage();
    int GetSessionId();
    int GetmediationId();

    // Base Class Virtual Overrides
    QString Parse(void);
    QString UpdateParse();
    QString GetIdRowName();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();

    void print(QTextCursor cursor);

};

#endif // NOTEFORM_H
