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

        primitives::Dimension getMinSize () const { return minSize; }
        void setMinSize (const primitives::Dimension &value) { minSize = value; }

        primitives::Dimension getMaxSize () const { return maxSize; }
        void setMaxSize (const primitives::Dimension &value) { maxSize = value; }

protected:
        AbstractActor *actor = nullptr; // Actor must be on stage, not on scale.
        primitives::Point startPoint;
        primitives::Point endPoint;
        primitives::Dimension minSize;
        primitives::Dimension maxSize;
        primitives::Point startPointActor; // In stage coords.
};

#endif // DASHEDCIRCLESTRATEGY_H
