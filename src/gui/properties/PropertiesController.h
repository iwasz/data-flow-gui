/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PROPERTIES_CONTROLLER_H_
#define PROPERTIES_CONTROLLER_H_

#include "view/IClutterActor.h"
#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>

/**
 *
 */
class __tiliae_reflect__ PropertiesController : public GtkForms::AbstractController {
public:
        PropertiesController ();
        virtual ~PropertiesController ();
        virtual GtkForms::ViewsToOpen onStart ();
        virtual void onSelection (ClutterActorVector *s);

private:

        struct Impl;
        Impl *impl;
};

#endif /* MainController_H_ */
