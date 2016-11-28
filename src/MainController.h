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
        MainController ();
        virtual ~MainController ();

        void init ();
        virtual std::string onStart ();
        virtual void onSubmit ();
        virtual void onIdle ();
        virtual void onStop ();


        void onNewNodeToolClicked (std::string const &name);
        void onStageClicked (float x, float y);
        void onReleased (float x, float y);
        void onMotion (float x, float y);

private:

        struct Impl;
        Impl *impl;
};

#endif /* MainController_H_ */
