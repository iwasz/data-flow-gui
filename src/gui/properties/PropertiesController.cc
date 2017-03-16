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
        IClutterActor *actor = nullptr;
};

/*****************************************************************************/

PropertiesController::PropertiesController () : impl (new Impl) {}

/*****************************************************************************/

PropertiesController::~PropertiesController () { delete impl; }

/*****************************************************************************/

GtkForms::ViewsToOpen PropertiesController::onStart ()
{
        set ("actor", Core::Variant (impl->actor));
        refresh ("actor.*");

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
                impl->actor = nullptr;
                replace (getName ());
                return;
        }

        impl->actor = selectedActors->front ();
        Core::StringVector v = impl->actor->getPropertyViews ();

        int cnt = 1;
        for (std::string const &n : v) {
                // TODO add all views to the same slot (gtkforms implementation necessary).
                std::string slotName = "rightSlot" + boost::lexical_cast<std::string> (cnt);
                impl->currentViews.add (n, slotName);
                ++cnt;
        }

        replace (getName ());
}
