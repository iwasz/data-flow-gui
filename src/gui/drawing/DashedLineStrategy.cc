/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedLineStrategy.h"

void DashedLineStrategy::onButtonPress (Point p, Object *o)
{
        startPoint = p;
        endPoint = Point ();
        line->setPointA (startPoint);
        line->setPointB (startPoint);
        line->setVisible (true);
}

/*****************************************************************************/

void DashedLineStrategy::onMotion (Point p, Object *o) { line->setPointB (p); }

/*****************************************************************************/

bool DashedLineStrategy::onButtonRelease (Point p, Object *o)
{
        line->setVisible (false);
        endPoint = p;
        return startPoint.x != endPoint.x || startPoint.y != endPoint.y;
}

/*****************************************************************************/

void DashedLineStrategy::onObjectCreated (IClutterActor *a)
{
        Line *l = dynamic_cast<Line *> (a);

        if (!l) {
                throw Core::Exception ("DashedLineStrategy::reshape could not cast actor to Line *");
        }

        l->setPointA (startPoint);
        l->setPointB (endPoint);
}
