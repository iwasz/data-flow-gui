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
 */
class __tiliae_reflect__ RectangularSelectorStrategy : public ShapeDrawStrategy {
public:
        virtual ~RectangularSelectorStrategy () {}
        virtual void onObjectCreated (IClutterActor *a);

        Rectangle *getRectangularSelector () const { return rectangularSelector; }
        void setRectangularSelector (Rectangle *value) { rectangularSelector = value; }

private:
        Rectangle *rectangularSelector = nullptr;
};

#endif // RECTANGULARSELECTORSTRATEGY_H
