//
//  MediatorKeys.h
//  mediator_test
//
//  Created by Lansdon Page on 5/25/14.
//  Copyright (c) 2014 Lansdon Page. All rights reserved.
//

#ifndef mediator_test_MediatorKeys_h
#define mediator_test_MediatorKeys_h

#include <string>


//////////////////////////////////////////////////////////////////
//				GUI EVENTS
// Everyting in this section is called by the GUI
// For example, when an intake form "submit" button on the gui
// is pressed, an event will be called which contains the form
// data as an argument. The BL will register to recieve that event.
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const std::string MKEY_GUI_SUBMIT_FRUIT_NAME = "MKEY_GUI_SUBMIT_FRUIT_NAME";                // std::string*

const std::string MKEY_GUI_SEARCH_FOR_USERNAME = "MKEY_GUI_SEARCH_FOR_USERNAME";           // std::string*

const std::string MKEY_GUI_SUBMIT_INTAKE_FORM = "MKEY_GUI_SUBMIT_INTAKE_FORM";              // Intake*
const std::string MKEY_GUI_LOAD_INTAKE_FORM = "MKEY_GUI_LOAD_INTAKE_FORM";                // Intake*

const std::string MKEY_GUI_AUTHENTICATE_USER = "MKEY_GUI_AUTHENTICATE_USER";                // User*


//////////////////////////////////////////////////////////////////
//				BUSINESS LOGIC EVENTS
// Everyting in this section is called by the BUSINESS LOGIC
// After the business logic validates an intake form
// it will fire an event containing the form data as an argument
// which the database has registered to recieve.
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const std::string MKEY_BL_VALIDATE_FRUITNAME_DONE = "MKEY_BL_VALIDATE_FRUITNAME_DONE";       // std::string*

const std::string MKEY_BL_RETURN_SEARCH_RESULTS = "MKEY_BL_RETURN_SEARCH_RESULTS";          // class Intake*

const std::string MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE = "MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE";   // Intake*
const std::string MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE = "MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE";   // Intake*

const std::string MKEY_BL_AUTHENTICATE_USER_DONE = "MKEY_BL_AUTHENTICATE_USER_DONE";   // Intake*



//////////////////////////////////////////////////////////////////
//				DB EVENTS
// Everyting in this section is called by the  DB
// For example, when an intake form is submitted to be
// persisted in the DB and DB is done. return results
// as an event for anyone listening to recieve.
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const std::string MKEY_DB_PERSIST_FRUIT_NAME_DONE = "MKEY_DB_PERSIST_FRUIT_NAME_DONE";       // nil
const std::string MKEY_DB_PERSIST_INTAKE_FORM_DONE = "MKEY_DB_PERSIST_INTAKE_FORM_DONE";      // Intake*
const std::string MKEY_DB_LOAD_INTAKE_FORM_DONE = "MKEY_DB_LOAD_INTAKE_FORM_DONE";      // std::vector<Intake*>*
const std::string MKEY_DB_AUTHENTICATE_USER_DONE = "MKEY_DB_LOAD_INTAKE_FORM_DONE";      // std::vector<Intake*>*


#endif
