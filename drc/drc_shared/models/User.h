#ifndef USER_H
#define USER_H

#include "DBBaseObject.h"
#include <QString>
#include "drctypes.h"
#include "Crypto/SHA256_Crypto.h"

/*!
 * \brief The User class
 */
class User : public DBBaseObject
{
private:
	QString m_userName;
	QString m_password;
    UserTypes m_type;

public:
	User();
    User(QString name, QString pass, UserTypes type = USER_T_NORMAL);

    QString GetName(void);
    void SetName(QString name);
    QString GetPass(void);
    void SetPassword(QString password);

    UserTypes GetType(void);
    void SetType(UserTypes Type);
    QString GetTypeString(void);

    QString Parse(void);
    QString ColumnNames();
    QString UpdateParse();

    QString GetIdRowName();

    QString table(void);

    QString DuplicateQuery(void);

    QString SearchQuery(void);
};

#endif
