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
        // ConsoleView acts as a model here, and GtkToolToggleButton is populated with its 'autoScroll' value.
        set ("console", Core::Variant (consoleView));
        // Part of the view is refreshed.
        refresh ("console.autoScroll");
        // But in onStart method, getView returns nullptr, because we didnt even returned the view's name, so this is why I added consoleView class field.
        return "consoleView->bottomSlot";
}
