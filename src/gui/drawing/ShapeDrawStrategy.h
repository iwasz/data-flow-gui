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

        virtual void onButtonPress (Event const &e);
        virtual void onMotion (Event const &e);
        virtual bool onButtonRelease (Event const &e);
        virtual void onObjectCreated (IClutterActor *a);

        AbstractActor *getActor () const { return actor; }
        void setActor (AbstractActor *value) { actor = value; }

        Dimension getMinSize () const { return minSize; }
        void setMinSize (const Dimension &value) { minSize = value; }

protected:
        AbstractActor *actor = nullptr; // Actor must be on stage, not on scale.
        Point startPoint;
        Point endPoint;
        Dimension minSize;
        Point startPointActor; // In stage coords.
};

#endif // DASHEDCIRCLESTRATEGY_H
