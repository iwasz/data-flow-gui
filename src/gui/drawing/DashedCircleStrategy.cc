/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedCircleStrategy.h"

void DashedCircleStrategy::onButtonPress (float x, float y)
{
        startPoint = Point (x, y);
        endPoint = Point ();
        circle->setPosition (Point (x, y));
        circle->setSize (Dimension ());
        circle->setVisible (true);
}

/*****************************************************************************/

void DashedCircleStrategy::onMotion (float x, float y) { circle->setSize (Point (x, y) - startPoint); }

/*****************************************************************************/

void DashedCircleStrategy::onButtonRelease (float x, float y)
{
        circle->setVisible (false);
        endPoint = Point (x, y);
}

/*****************************************************************************/

void DashedCircleStrategy::reshape (IClutterActor *a)
{
        a->setPosition (startPoint);
        a->setSize (endPoint - startPoint);
}
