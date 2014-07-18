#include "clientsessiondata.h"

ClientSessionData::ClientSessionData()
{
    paid = attyDidAttend = attySaidAttend = atTable = false;
    support = 0;
}

QString ClientSessionData::Parse()
{
#warning TODO - Parse() UNIMPLEMENTED!!!!
    return "";
}

QString ClientSessionData::UpdateParse()
{
#warning TODO - UpdateParse() UNIMPLEMENTED!!!!
    return "";

}

QString ClientSessionData::table()
{
#warning TODO - table() UNIMPLEMENTED!!!!
    return "";

}

QString ClientSessionData::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!
    return "";

}

QString ClientSessionData::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!
    return "";

}

QString ClientSessionData::GetIdRowName()
{
#warning TODO - GetIdRowName() UNIMPLEMENTED!!!!
    return "";

}

void ClientSessionData::on_atty_will_attend(bool value)
{
    setAttySaidAttend(value);
}

void ClientSessionData::on_atty_did_attend(bool value)
{
    setAttyDidAttend(value);
}

void ClientSessionData::on_support(uint value)
{
    setSupport(value);
}

bool ClientSessionData::isPaid() const
{
    return ((!isNoFee()) && paid);
}

bool ClientSessionData::isNoFee() const
{
    return (fee.isEmpty() || (fee.toDouble() == 0));
}

void ClientSessionData::print(QTextCursor &cursor)
{
    cursor.insertText("\tAt Table: ");
    if(atTable)
        cursor.insertText("Yes");
    else
        cursor.insertText("No");
    cursor.insertText("  Fee: " + fee + "  Income: " + income + "  Paid: ");
    if(paid)
        cursor.insertText("Yes\n");
    else
        cursor.insertText("No\n");
    cursor.insertText("\tAttorney: Said: ");
    if(attySaidAttend)
        cursor.insertText("Yes");
    else
        cursor.insertText("No");
    cursor.insertText(" Did: ");
    if(attyDidAttend)
        cursor.insertText("Yes");
    else
        cursor.insertText("No");
    cursor.insertText(" Support: " + QString::number(support) + "\n");

}
