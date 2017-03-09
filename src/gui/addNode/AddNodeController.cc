/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AddNodeController.h"
#include "gui/main/MainController.h"
#include <App.h>
#include <Logging.h>
#include <unistd.h>

static src::logger_mt &lg = logger::get ();

std::string AddNodeController::onStart ()
{
        set ("tools", Core::Variant (tools));
        refresh ("");
        return "addNodeView";
}

/*
 * Po konwersji wykonuje się metoda IController::onSubmit:
 */
void AddNodeController::onSubmit () { refresh ("nodesList", "filter"); }

/*****************************************************************************/

void AddNodeController::onRowActivated (Core::Variant const &row)
{
        if (row.isNone () || row.isNull ()) {
                return;
        }

        void const *rawRow = vcast<void const *> (row);
        Tool const *tool = static_cast<Tool const *> (rawRow);
        mainController->onNewNodeToolClicked (tool->name);
        closeThis ();
}

/*****************************************************************************/

void AddNodeController::onRowSelected (Core::Variant const &row)
{
        if (row.isNone () || row.isNull ()) {
                set ("description", Core::Variant ());
                refresh ("description");
                set ("imagePath", Core::Variant ());
                refresh ("imageDesc");
                currentSelection = "";
                return;
        }

        void const *rawRow = vcast<void const *> (row);
        Tool const *tool = static_cast<Tool const *> (rawRow);

        set ("description", Core::Variant (tool->description));
        refresh ("description");
        set ("imagePath", Core::Variant (tool->imagePath));
        refresh ("imageDesc");

        currentSelection = tool->name;
}

/*****************************************************************************/

void AddNodeController::onOk ()
{
//        if (!currentSelection.empty ()) {
//                mainController->onNewNodeToolClicked (currentSelection);
//                closeThis ();
//        }
}
