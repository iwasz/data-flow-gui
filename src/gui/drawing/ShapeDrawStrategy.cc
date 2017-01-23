/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ShapeDrawStrategy.h"

void ShapeDrawStrategy::onButtonPress (const Event &e)
{
        startPoint = e.positionParentCoords;
        endPoint = Point ();

        startPointActor = e.positionStageCoords;
        actor->setPosition (startPointActor);
        actor->setSize (Dimension ());
        actor->setVisible (true);
}

/*****************************************************************************/

void ShapeDrawStrategy::onMotion (const Event &e) { actor->setSize (e.positionStageCoords - startPointActor); }

/*****************************************************************************/

bool ShapeDrawStrategy::onButtonRelease (const Event &e)
{
        actor->setVisible (false);
        endPoint = e.positionParentCoords;
        return (startPoint.x != endPoint.x && startPoint.y != endPoint.y) || (minSize.height && minSize.width);
}

/*****************************************************************************/

void ShapeDrawStrategy::onObjectCreated (IClutterActor *a)
{
        a->setPosition (startPoint);
        Dimension size = endPoint - startPoint;

        if (minSize.height > 0 || minSize.width > 0) {
                if (size.height < minSize.height) {
                        size.height = minSize.height;
                }

                if (size.width < minSize.width) {
                        size.width = minSize.width;
                }
        }

        a->setSize (size);
}
