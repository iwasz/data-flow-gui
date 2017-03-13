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
        virtual ~PropertiesController () {}
        virtual std::string onStart ();
        virtual void onSelection (ClutterActorVector *s);
};

#endif /* MainController_H_ */
