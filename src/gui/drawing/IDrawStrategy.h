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
        virtual void onButtonPress (float x, float y) = 0;
        /// Mouse motion while button still pressed.
        virtual void onMotion (float x, float y) = 0;
        /// Button released.
        virtual void onButtonRelease (float x, float y) = 0;
        /**
         * This get called after all 3 above, and after a factory kicked in, and created an *a.
         * It's purpose is to set *a it's final shape.
         */
        virtual void reshape (IClutterActor *a) = 0;
};

#endif // IDRAWSTRATEGY_H
