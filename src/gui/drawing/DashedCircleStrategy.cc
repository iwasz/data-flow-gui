/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedCircleStrategy.h"

void DashedCircleStrategy::onButtonPress (Point p, Core::Object *o)
{
        startPoint = p;
        endPoint = Point ();

        circle->setPosition (p);
        circle->setSize (Dimension ());
        circle->setVisible (true);
}

/*****************************************************************************/

void DashedCircleStrategy::onMotion (Point p, Core::Object *o) { circle->setSize (p - startPoint); }

/*****************************************************************************/

bool DashedCircleStrategy::onButtonRelease(Point p, Object *o)
{
        circle->setVisible (false);
        endPoint = p;
        return  startPoint.x != endPoint.x && startPoint.y != endPoint.y;
}

/*****************************************************************************/

void DashedCircleStrategy::reshape (IClutterActor *a)
{
        a->setPosition (startPoint);
        a->setSize (endPoint - startPoint);
}
