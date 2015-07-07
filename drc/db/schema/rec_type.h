#ifndef REC_TYPE_H
#define REC_TYPE_H

enum RECORD_TYPE
{
    // IDs
    PRIMARY_ID,
    SECONDARY_ID,

    // Person Info
    FIRST_NAME,
    MIDDLE_NAME,
    LAST_NAME,
    PHONE_NUMBER,
    PHONE_EXT,
    EMAIL,
    ADDRESS,
    CITY,
    COUNTY,
    STATE,

    // DateTimes
    UPPER_DATE,
    MIDDLE_DATE,
    LOWER_DATE,
    UPPER_DATETIME,
    MIDDLE_DATETIME,
    LOWER_DATETIME,
    NEW_UPPER_DATETIME,  // hack for Session Table
    NEW_MIDDLE_DATETIME,
    NEW_LOWER_DATETIME,

    // Data
    STRING,
    INT_BOOL,
    BOOL,
    DOUBLE,
    INT,

    // Specific Columns     (Ranges)
    EVALUATION_SCORE,       // 0-10
    SUPPORT,                // 0-2
    DISPUTE_TYPE,           // 1-14
    DISPUTE_STATE,          // 1-4
    DISPUTE_INTERNAL_STATE, // 1-10
    REFERRAL_SOURCE,        // 1-16
    INQUIRY_TYPE,           // 1-4
    COUNTY_NAME,            // 1-6
    SESSION_STATUS,         // 1-4
    SESSION_OUTCOME,        // 0-9

    // Login
    USER_NAME,
    PASSWORD,
    ADMIN_BOOL
};


#endif // REC_TYPE_H

