/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONSOLE_CONTROLLER_H_
#define CONSOLE_CONTROLLER_H_

#include "ConsoleBuffer.h"
#include "ConsoleView.h"
#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>

/**
 *
 */
class __tiliae_reflect__ ConsoleController : public GtkForms::AbstractController {
public:
        virtual ~ConsoleController () {}

        virtual std::string onStart ();
        void onClear () { console->clear (); }

public:
        ConsoleBuffer *console = nullptr;
        ConsoleView *consoleView = nullptr; // Needed in onStart as model. See comment there.
};

#endif /* MainController_H_ */
