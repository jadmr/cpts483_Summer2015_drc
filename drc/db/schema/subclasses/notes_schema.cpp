#include "notes_schema.h"


NotesSchema::NotesSchema() : DatabaseSchema()
{
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

    notesColumnType.append(ID);
    notesColumnType.append(ID);
    notesColumnType.append(ID);
    notesColumnType.append(STRING);
    notesColumnType.append(DATE_TIME);

    setColumnType(notesColumnType);
}

#define OVERRIDES_OF_BASE }
