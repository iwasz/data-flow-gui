/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef RECTANGULARSELECTORSTRATEGY_H
#define RECTANGULARSELECTORSTRATEGY_H

#include "ShapeDrawStrategy.h"

class Rectangle;

/**
 * Responsible for drawing the selection rectangle, and managing sleected objects.
 * TODO selecting single objects by clicking on them
 * TODO Expanding existing selection with modifier key (Shift/Ctrl + select).
 */
class __tiliae_reflect__ RectangularSelectorStrategy : public ShapeDrawStrategy {
public:
        virtual ~RectangularSelectorStrategy () {}
        virtual void onObjectCreated (IClutterActor *a);

        void onButtonPress (Point p, Core::Object *o);

        Rectangle *getRectangularSelector () const { return rectangularSelector; }
        void setRectangularSelector (Rectangle *value) { rectangularSelector = value; }

        ClutterActorVector *getSelectedActors () { return selectedActors; }
        void setSelectedActors (ClutterActorVector *value) { selectedActors = value; }

        void unselectAll ();

private:
        Rectangle *rectangularSelector = nullptr;
        ClutterActorVector *selectedActors = nullptr;
};

#endif // RECTANGULARSELECTORSTRATEGY_H
