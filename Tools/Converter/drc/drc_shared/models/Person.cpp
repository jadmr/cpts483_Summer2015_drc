#include "Person.h"
#include <sstream>

Person::Person()
{
//    _firstName = "";
    _county = COUNTY_NONE;
    _numberInHousehold = 0;
    _numberChildrenInHousehold = 0;
    _county = COUNTY_NONE;
}

Person::Person(QString n)
{
    _county = COUNTY_NONE;
    _numberInHousehold = 0;
    _numberChildrenInHousehold = 0;
    _county = COUNTY_NONE;
}

Person::~Person()
{

}

bool Person::operator==(const Person &rhs)
{
    bool result = true;
    if(this->getFirstName() == rhs.getFirstName()
            && this->getLastName() == rhs.getLastName()
            && this->getMiddleName() == rhs.getMiddleName())
        result = false;
    return result;
}

bool Person::operator!=(const Person &rhs)
{

    return !(*this==rhs);
}

QString Person::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!

    return "";
}

QString Person::SearchQuery()
{
    QString toReturn = "";
    QString percent  = "%";
    bool notFirstField = false;

    if(this->getFirstName() != "")
    {
        toReturn += QString("first_name like '%2%1%2'")
                .arg(this->getFirstName().replace("'", "''"))
                .arg(percent);
        notFirstField = true;
    }
    if(this->getMiddleName() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("middle_name like '%2%1%2'")
                .arg(this->getMiddleName().replace("'", "''"))
                .arg(percent);
    }
    if(this->getLastName() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("last_name like '%2%1%2'")
                .arg(this->getLastName().replace("'", "''"))
                .arg(percent);
    }
    if(this->getStreet() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("street_name like '%2%1%2'")
                .arg(this->getStreet().replace("'", "''"))
                .arg(percent);
    }
    if(this->getUnit() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("unit_name like '%2%1%2'")
                .arg(this->getUnit().replace("'", "''"))
                .arg(percent);
    }
    if(this->getCity() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("city_name like '%2%1%2'")
                .arg(this->getCity().replace("'", "''"))
                .arg(percent);
    }
    if(this->getState() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("state_name like '%2%1%2'")
                .arg(this->getState().replace("'", "''"))
                .arg(percent);
    }
    if(this->getZip() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("zip_code like '%2%1%2'")
                .arg(this->getZip().replace("'", "''"))
                .arg(percent);
    }

    if(this->getPrimaryPhone() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("primary_phone like '%2%1%2'")
                .arg(this->getPrimaryPhone().replace("'", "''"))
                .arg(percent);
    }
    if(this->getSecondaryPhone() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("secondary_phone like '%2%1%2'")
                .arg(this->getSecondaryPhone().replace("'", "''"))
                .arg(percent);
    }
    if(this->getAssistantPhone() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("assistance_phone like '%2%1%2'")
                .arg(this->getAssistantPhone().replace("'", "''"))
                .arg(percent);
    }
    if(this->getEmail() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("email_address like '%2%1%2'")
                .arg(this->getEmail().replace("'", "''"))
                .arg(percent);
    }
    if(this->getNumberInHousehold() != 0)
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("number_in_house = %1").arg(this->getNumberInHousehold());
    }
    if(this->getAttorney() != "")
    {
        if(notFirstField)
        {
            toReturn += " AND ";
        }
        else
        {
            notFirstField = true;
        }
        toReturn += QString("attorney_name like '%2%1%2'")
                .arg(this->getAttorney().replace("'", "''"))
                .arg(percent);
    }


    return toReturn;
}


// Test Data - Fill the object with test values in every field.
Person *Person::SampleData()
{
    Person *result = new Person();

    // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    QString strId = QString::fromStdString(ss.str());

    result->setFirstName(QString("firstname" + strId));
    result->setMiddleName(QString("middlename" + strId));
    result->setLastName(QString("lastname" + strId));
    result->setStreet(QString("street" + strId));
    result->setUnit(QString("unit" + strId));
    result->setCity(QString("city" + strId));
    result->setZip(QString("zip" + strId));
//    result->setCounty(QString("county" + strId));
    result->setState(QString("state" + strId));
    result->setPrimaryPhone(QString("PPhone" + strId));
    result->setPrimaryPhoneExt(QString("PPhoneExt" + strId));
    result->setSecondaryPhone(QString("SPhone" + strId));
    result->setSecondaryPhoneExt(QString("SPhoneExt" + strId));
    result->setAssistantPhone(QString("APhone" + strId));
    result->setAssistantPhoneExt(QString("APhoneExt" + strId));
    result->setEmail(QString("email" + strId));
    result->setNumberInHousehold((unsigned int)_SAMPLE_INDEX);
    result->setAttorney(QString("attorney" + strId));

    return result;
}

QString Person::ColumnNames()
{
    //Name
    QString column_names = QString("%1, %2, %3, %4,")
        .arg(QString("Person_id"))
        .arg(QString("first_name"))
        .arg(QString("middle_name"))
        .arg(QString("last_name"));

    //Address
    column_names += QString(" %1, %2, %3, %4, %5, %6,")
        .arg(QString("street_name"))
        .arg(QString("unit_name"))
        .arg(QString("city_name"))
        .arg(QString("state_name"))
        .arg(QString("zip_code"))
        .arg(QString("county_name"));

    //Contact
    column_names += QString(" %1, %2, %3, %4, %5")
        .arg(QString("primary_phone"))
        .arg(QString("primary_phone_ext"))
        .arg(QString("secondary_phone"))
        .arg(QString("secondary_phone_ext"))
        .arg(QString("email_address"));

    //Household
    // column_names += QString(" %1, %2,")
    //     .arg(QString("number_adult_in_house"))
    //     .arg(QString("number_children_in_house"));

    //Legal Representation
    // column_names += QString(" %1, %2, %3, %4, %5, %6")
    //     .arg(QString("attorney_name"))
    //     .arg(QString("attorney_phone"))
    //     .arg(QString("attorney_email"))
    //     .arg(QString("assistant_name"))
    //     .arg(QString("assistant_phone"))
    //     .arg(QString("assistant_email"));

    QString toReturn = QString("(%1)")
            .arg(column_names);

    return toReturn;
}

QString Person::Parse(void)
{
    //Name
    QString column_values = QString("%1, '%2', '%3', '%4',")
        .arg(QString("null"))
        .arg(this->getFirstName().replace("'", "''"))
        .arg(this->getMiddleName().replace("'", "''"))
        .arg(this->getLastName().replace("'", "''"));

    //Address
    column_values += QString(" '%1', '%2', '%3', '%4', '%5', '%6',")
        .arg(this->getStreet().replace("'", "''"))
        .arg(this->getUnit().replace("'", "''"))
        .arg(this->getCity().replace("'", "''"))
        .arg(this->getState().replace("'", "''"))
        .arg(this->getZip().replace("'", "''"))
        .arg(QString::number(this->getCounty()));

    //Contact
    column_values += QString(" '%1', '%2', '%3', '%4', '%5'")
        .arg(this->getPrimaryPhone().replace("'", "''"))
        .arg(this->getPrimaryPhoneExt().replace("'", "''"))
        .arg(this->getSecondaryPhone().replace("'", "''"))
        .arg(this->getSecondaryPhoneExt().replace("'", "''"))
        .arg(this->getEmail().replace("'", "''"));

    //Other
    // column_values += QString(" %1, %2,")
    //     .arg(this->getNumberInHousehold())
    //     .arg(this->getNumberChildrenInHousehold());

    // column_values += QString(" '%1', '%2', '%3', '%4', '%5', '%6'")
    //     .arg(this->getAttorney().replace("'", "''"))
    //     .arg(this->getAttorneyPhone().replace("'", "''"))
    //     .arg(this->getAttorneyEmail().replace("'", "''"))
    //     .arg(this->getAssistantName().replace("'", "''"))
    //     .arg(this->getAssistantPhone().replace("'", "''"))
    //     .arg(this->getAssistantEmail().replace("'", "''"));

    return column_values;
}

QString Person::UpdateParse()
{
    //Name
    QString toUpdate = QString("First_Name = '%1', middle_name = '%2', last_name = '%3',")
            .arg(this->getFirstName().replace("'", "''"))
            .arg(this->getMiddleName().replace("'", "''"))
            .arg(this->getLastName().replace("'", "''"));

    //Address
    toUpdate += QString(" street_name = '%1', unit_name = '%2', city_name = '%3', state_name = '%4', zip_code = '%5', county_name = '%6',")
            .arg(this->getStreet().replace("'", "''"))
            .arg(this->getUnit().replace("'", "''"))
            .arg(this->getCity().replace("'", "''"))
            .arg(this->getState().replace("'", "''"))
            .arg(this->getZip().replace("'", "''"))
            .arg(QString::number(this->getCounty()));

    //Phone Number
    toUpdate += QString(" primary_phone =  '%1', primary_phone_ext = '%2', secondary_phone = '%3', secondary_phone_ext = '%4', email_address = '%5'")//' assistance_phone = '%3',")
            .arg(this->getPrimaryPhone().replace("'", "''"))
            .arg(this->getPrimaryPhoneExt().replace("'", "''"))
            .arg(this->getSecondaryPhone().replace("'", "''"))
            .arg(this->getSecondaryPhoneExt().replace("'", "''"))
            .arg(this->getEmail().replace("'", "''"));

    //Other
//    toUpdate += QString(" email_address = '%1', number_in_house = %2, number_children_in_house = %3, attorney_name = '%4'")
//            .arg(this->getEmail().replace("'", "''"))
//            .arg(this->getNumberInHousehold())
//            .arg(this->getNumberChildrenInHousehold())
//            .arg(this->getAttorney().replace("'", "''"));

    return toUpdate;
}

QString Person::GetIdRowName()
{
    return "Person_id";
}

QString Person::table(void)
{
    return QString("Person_Table");
}
