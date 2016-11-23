/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAIN_CONTROLLER_H_
#define MAIN_CONTROLLER_H_

#include <string>
#include <controller/AbstractController.h>
#include <ReflectionParserAnnotation.h>

class __tiliae_reflect__ MainController : public GtkForms::AbstractController {
public:
        MainController () {}
        virtual ~MainController () {}

        virtual std::string onStart ();
        virtual void onSubmit ();
        virtual void onIdle ();
        virtual void onStop ();
};

#endif /* MainController_H_ */
