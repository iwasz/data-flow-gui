/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedLineStrategy.h"

void DashedLineStrategy::onButtonPress (const Event &e)
{
        startPoint = e.positionParentCoords;
        endPoint = Point ();
        line->setPointA (e.positionStageCoords);
        line->setPointB (e.positionStageCoords);
        line->setVisible (true);
}

/*****************************************************************************/

void DashedLineStrategy::onMotion (const Event &e) { line->setPointB (e.positionStageCoords); }

/*****************************************************************************/

bool DashedLineStrategy::onButtonRelease (const Event &e)
{
        line->setVisible (false);
        endPoint = e.positionParentCoords;
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
