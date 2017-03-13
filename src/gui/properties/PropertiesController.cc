/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "PropertiesController.h"
#include <App.h>
#include <Logging.h>

static src::logger_mt &lg = logger::get ();

std::string PropertiesController::onStart ()
{
        set ("fillTest", Core::Variant (true));
        set ("labelTest", Core::Variant ("Hello world"));
        refresh ("fillTest");
        refresh ("labelTest");
        // return "propertiesView";
        return "abstractActorPropertiesView->rightSlot1, buttonPropertiesView->rightSlot2";
}
