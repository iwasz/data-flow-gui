/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef RECTANGULARSELECTORSTRATEGY_H
#define RECTANGULARSELECTORSTRATEGY_H

#include "ISelectorStrategy.h"
#include "ShapeDrawStrategy.h"

class Rectangle;
class ScaleLayer;

/**
 * Responsible for drawing the selection rectangle, and managing sleected objects.
 */
class __tiliae_reflect__ RectangularSelectorStrategy : public ShapeDrawStrategy, public ISelectorStrategy {
public:
        virtual ~RectangularSelectorStrategy () {}
        virtual void onObjectCreated (IClutterActor *a);

        void onButtonPress (Event const &e);
//        bool onButtonRelease (const Event &e);

        Rectangle *getRectangularSelector () const { return rectangularSelector; }
        void setRectangularSelector (Rectangle *value) { rectangularSelector = value; }

        ClutterActorVector *getSelectedActors () { return selectedActors; }
        void setSelectedActors (ClutterActorVector *value) { selectedActors = value; }

        void unselectAll ();

        ScaleLayer *getScaleLayer () const { return scaleLayer; }
        void setScaleLayer (ScaleLayer *value) { scaleLayer = value; }

private:
        Rectangle *rectangularSelector = nullptr;
        ClutterActorVector *selectedActors = nullptr;
        ScaleLayer *scaleLayer = nullptr;
};

#endif // RECTANGULARSELECTORSTRATEGY_H
