/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ISELECTORSTRATEGY_H
#define ISELECTORSTRATEGY_H

#include <ReflectionParserAnnotation.h>
#include <core/Object.h>
#include <view/IClutterActor.h>

class ScaleLayer;

/**
 * Responsible for selecting objects on the stage.
 */
struct __tiliae_reflect__ ISelectorStrategy : public virtual Core::Object {
        virtual ~ISelectorStrategy () {}

        virtual ClutterActorVector *getSelectedActors () = 0;
        virtual void setSelectedActors (ClutterActorVector *value) = 0;

        virtual void unselectAll () = 0;

        virtual ScaleLayer *getScaleLayer () const = 0;
        virtual void setScaleLayer (ScaleLayer *value) = 0;
};

#endif // ISELECTORSTRATEGY_H
