/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "OpenFileController.h"
#include <App.h>
#include <Logging.h>

static src::logger_mt &lg = logger::get ();

GtkForms::ViewsToOpen OpenFileController::onStart () { return "openFileView"; }

/*****************************************************************************/

void OpenFileController::onResponse (int responseId, std::string const &path)
{
        if (responseId == GTK_RESPONSE_ACCEPT) {
                loadService->load (path);
                closeThis ();
                // ff->save ("/home/iwasz/file.xml");
        }
}
