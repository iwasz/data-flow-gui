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

class Rect;
class ScaleLayer;

/**
 * Responsible for drawing the selection rectangle, and managing sleected objects.
 */
class __tiliae_reflect__ RectangularSelectorStrategy : public ShapeDrawStrategy, public ISelectorStrategy {
public:
        virtual ~RectangularSelectorStrategy () {}
        virtual void onObjectCreated (IClutterActor *a) __tiliae_no_reflect__;
        virtual void onObjectCreated (IClutterActor *a, bool inside) __tiliae_no_reflect__;

        void onButtonPress (Event const &e);

        Rect *getRectangularSelector () const { return rectangularSelector; }
        void setRectangularSelector (Rect *value) { rectangularSelector = value; }

        ClutterActorVector *getSelectedActors () { return selectedActors; }
        void setSelectedActors (ClutterActorVector *value) { selectedActors = value; }

        void unselectAll ();

        ScaleLayer *getScaleLayer () const { return scaleLayer; }
        void setScaleLayer (ScaleLayer *value) { scaleLayer = value; }

private:
        Rect *rectangularSelector = nullptr;
        ClutterActorVector *selectedActors = nullptr;
        ScaleLayer *scaleLayer = nullptr;
};

#endif // RECTANGULARSELECTORSTRATEGY_H
