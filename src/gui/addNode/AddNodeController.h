/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADD_NODE_CONTROLLER_H_
#define ADD_NODE_CONTROLLER_H_

#include "gui/main/Tool.h"
#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>

class MainController;

/**
 * @brief The MainController class
 */
class __tiliae_reflect__ AddNodeController : public GtkForms::AbstractController {
public:
        AddNodeController () {}
        virtual ~AddNodeController () {}

        virtual GtkForms::ViewsToOpen onStart ();
        virtual void onSubmit ();
        void onRowActivated (const Core::Variant &row);
        void onRowSelected (const Core::Variant &row);
        void onOk ();

public:

        ToolCategoryVector *tools = nullptr;
        MainController *mainController = nullptr;

private:
        std::string currentSelection;
};

#endif /* MainController_H_ */
