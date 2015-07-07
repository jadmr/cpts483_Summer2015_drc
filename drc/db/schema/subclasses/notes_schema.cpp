#include "notes_schema.h"


NotesSchema::NotesSchema() : DatabaseSchema()
{
    setTableName("Notes_Table");

    initializeHeaders();
    initializeColumnTypes();
}

#define OVERRIDES_OF_BASE {

void NotesSchema::initializeHeaders()
{
    QVector<QString> notesHeaders;

    notesHeaders.append("Note_id");
    notesHeaders.append("Process_id");
    notesHeaders.append("Session_id");
    notesHeaders.append("Note");
    notesHeaders.append("CreateDate");

    setHeader(notesHeaders);
}

void NotesSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> notesColumnType;

    notesColumnType.append(PRIMARY_ID);
    notesColumnType.append(SECONDARY_ID);
    notesColumnType.append(SECONDARY_ID);
    notesColumnType.append(STRING);
    notesColumnType.append(MIDDLE_DATETIME);

    setColumnType(notesColumnType);
}

#define OVERRIDES_OF_BASE }
