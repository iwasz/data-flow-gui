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

void ShapeDrawStrategy::onMotion (const Event &e)
{
        Dimension req = e.positionStageCoords - startPointActor;

        if (maxSize.height > 0 && maxSize.width > 0) {
                if (req.height > maxSize.height) {
                        req.height = maxSize.height;
                }
                if (req.width > maxSize.width) {
                        req.width = maxSize.width;
                }
        }

        actor->setSize (req);
}

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

        if (maxSize.height > 0 && maxSize.width > 0) {
                if (size.height > maxSize.height) {
                        size.height = maxSize.height;
                }
                if (size.width > maxSize.width) {
                        size.width = maxSize.width;
                }
        }

        a->setSize (size);
}
