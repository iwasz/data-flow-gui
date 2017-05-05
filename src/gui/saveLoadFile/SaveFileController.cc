/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SaveFileController.h"
#include <App.h>
#include <Logging.h>

static src::logger_mt &lg = logger::get ();

GtkForms::ViewsToOpen SaveFileController::onStart () { return "saveFileView"; }

/*****************************************************************************/

void SaveFileController::onResponse (int responseId, std::string const &path)
{
        if (responseId == GTK_RESPONSE_ACCEPT) {
                saveService->save (path);
                closeThis ();
        }
}
