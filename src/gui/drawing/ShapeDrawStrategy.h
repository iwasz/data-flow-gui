/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHAPE_DRAW_STRATEGY_H
#define SHAPE_DRAW_STRATEGY_H

#include "IDrawStrategy.h"
#include "view/Circle.h"
#include <ReflectionParserAnnotation.h>

class __tiliae_reflect__ ShapeDrawStrategy : public IDrawStrategy {
public:
        virtual ~ShapeDrawStrategy () {}
        virtual void onButtonPress (Point p, Core::Object *o);
        virtual void onMotion (Point p, Core::Object *o);
        virtual bool onButtonRelease (Point p, Core::Object *o);
        virtual void onObjectCreated (IClutterActor *a);

        AbstractActor *getActor () const { return actor; }
        void setActor (AbstractActor *value) { actor = value; }

        Dimension getMinSize () const { return minSize; }
        void setMinSize (const Dimension &value) { minSize = value; }

protected:
        AbstractActor *actor = nullptr;
        Point startPoint;
        Point endPoint;
        Dimension minSize;
};

#endif // DASHEDCIRCLESTRATEGY_H
