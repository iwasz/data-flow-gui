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

struct PropertiesController::Impl {
        GtkForms::ViewsToOpen currentViews;
};

/*****************************************************************************/

PropertiesController::PropertiesController () : impl (new Impl) {}

/*****************************************************************************/

PropertiesController::~PropertiesController () { delete impl; }

/*****************************************************************************/

GtkForms::ViewsToOpen PropertiesController::onStart ()
{
        set ("fillTest", Core::Variant (true));
        set ("labelTest", Core::Variant ("Hello world"));
        refresh ("fillTest");
        refresh ("labelTest");
        // return "propertiesView";
        // return "abstractActorPropertiesView->rightSlot1, buttonPropertiesView->rightSlot2";
        return impl->currentViews;
}

/*****************************************************************************/

void PropertiesController::onSelection (ClutterActorVector *selectedActors)
{
        impl->currentViews.clear ();

        if (selectedActors->size () != 1) {
                // Default view
                replace (getName ());
                return;
        }

        IClutterActor *actor = selectedActors->front ();
        Core::StringVector v = actor->getPropertyViews ();

        int cnt = 1;
        for (std::string const &n : v) {
                std::string slotName = "rightSlot" + boost::lexical_cast<std::string> (cnt);
                impl->currentViews.add (n, slotName);
                ++cnt;
        }

        replace (getName ());
}
