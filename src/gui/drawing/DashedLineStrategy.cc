/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedLineStrategy.h"

void DashedLineStrategy::onButtonPress (float x, float y)
{
        startPoint = Point (x, y);
        endPoint = Point ();
        line->setPointA (startPoint);
        line->setPointB (startPoint);
        line->setVisible (true);
}

/*****************************************************************************/

void DashedLineStrategy::onMotion (float x, float y) { line->setPointB (Point (x, y)); }

/*****************************************************************************/

bool DashedLineStrategy::onButtonRelease (float x, float y)
{
        line->setVisible (false);
        endPoint = Point (x, y);
        return startPoint.x != endPoint.x || startPoint.y != endPoint.y;
}

/*****************************************************************************/

void DashedLineStrategy::reshape (IClutterActor *a)
{
        Line *l = dynamic_cast<Line *> (a);

        if (!l) {
                throw Core::Exception ("DashedLineStrategy::reshape could not cast actor to Line *");
        }

        l->setPointA (startPoint);
        l->setPointB (endPoint);
}
