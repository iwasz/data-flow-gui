/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ConsoleController.h"
#include <App.h>
#include <Logging.h>

static src::logger_mt &lg = logger::get ();

std::string ConsoleController::onStart ()
{
        return "consoleView->bottomSlot";
}

