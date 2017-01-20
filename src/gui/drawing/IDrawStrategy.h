/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDRAWSTRATEGY_H
#define IDRAWSTRATEGY_H

#include <ReflectionParserAnnotation.h>
#include <core/Object.h>
#include "view/IClutterActor.h"

struct __tiliae_reflect__ IDrawStrategy : public Core::Object {
        virtual ~IDrawStrategy () {}
        /// When mouse mutton is pressed for the first time after the tool was selected.
        virtual void onButtonPress (Point p, Core::Object *o) = 0;
        /// Mouse motion while button still pressed.
        virtual void onMotion (Point p, Core::Object *o) = 0;
        /// Button released. Returns if creating an object with such dimensions makes even sense.
        virtual bool onButtonRelease (Point p, Core::Object *o) = 0;
        /**
         * This get called after all 3 above, and after a factory kicked in, and created an *a.
         * It's purpose is to set *a it's final shape.
         */
        virtual void onObjectCreated (IClutterActor *a) = 0;
};

#endif // IDRAWSTRATEGY_H
