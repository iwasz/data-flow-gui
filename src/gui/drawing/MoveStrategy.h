/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

#include "primitives/Geometry.h"
#include <core/Object.h>
#include <clutter/clutter.h>

class MoveStrategy {
public:
        virtual ~MoveStrategy () {}

        virtual void onEnter (Point p, Core::Object *o);
        virtual void onMotion (Point p, Core::Object *o) {}
        virtual void onLeave (Point p, Core::Object *o);

private:

        ClutterActor *movingActor = nullptr;
        ClutterAction *dragAction = nullptr;
};

#endif // MOVESTRATEGY_H
