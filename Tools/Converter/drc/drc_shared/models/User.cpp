#include "User.h"

User::User()
{
    // filler!  Because this REALLY doesn't need to do anything.
}

User::User(QString name, QString pass, UserTypes type)
{
    m_userName = name;
    m_password = sha256(pass, "");
    m_type = type;
}

QString User::GetName(void)
{
    return m_userName;
}

QString User::GetPass(void)
{
    return m_password;
}

void User::SetName(QString name)
{
    m_userName = name;
}

void User::SetType(UserTypes Type)
{
    m_type = Type;
}

void User::SetPassword(QString password)
{
    m_password = sha256(password, "");
}

QString User::GetTypeString(void)
{
    switch(m_type)
    {
        case USER_T_ADMIN: return "Admin"; break;
        case USER_T_NORMAL: return "User"; break;
        default: return "Invalid"; break;
    }
}

UserTypes User::GetType(void)
{
    return m_type;
}

QString User::ColumnNames()
{
    QString column_names = QString("%1, %2, %3, %4")
            .arg(QString("user_id"))
            .arg(QString("userName"))
            .arg(QString("password"))
            .arg(QString("Admin"));

    QString toReturn = QString("(%1)")
            .arg(column_names);

    return toReturn;
}

QString User::Parse()
{   
    QString column_values = QString("%1, '%2', '%3', '%4'")
            .arg(QString("null"))
            .arg(this->GetName())
            .arg(this->GetPass())
            .arg(QString::number(this->GetType()));

//    QString toReturn = QString("(%1) VALUES(%2)")
//        .arg(column_names)
//        .arg(column_values);

    return column_values;
}

QString User::GetIdRowName()
{
    return "userName";
}

QString User::UpdateParse()
{
    return QString("userName = '%1', password = '%2', admin = '%3'")
            .arg(this->GetName())
            .arg(this->GetPass())
            .arg(QString::number(this->GetType()));
}

QString User::table(void)
{
    return QString("User_Table");
}

QString User::DuplicateQuery(void)
{
    return QString("This method in User.cpp has yet to be implemented.");
}

QString User::SearchQuery(void)
{
    return QString("This method in User.cpp has yet to be implemented.");
}
