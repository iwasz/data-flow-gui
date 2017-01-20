/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ShapeDrawStrategy.h"

void ShapeDrawStrategy::onButtonPress (Point p, Core::Object *o)
{
        startPoint = p;
        endPoint = Point ();

        actor->setPosition (p);
        actor->setSize (Dimension ());
        actor->setVisible (true);
}

/*****************************************************************************/

void ShapeDrawStrategy::onMotion (Point p, Core::Object *o) { actor->setSize (p - startPoint); }

/*****************************************************************************/

bool ShapeDrawStrategy::onButtonRelease (Point p, Object *o)
{
        actor->setVisible (false);
        endPoint = p;
        return (startPoint.x != endPoint.x && startPoint.y != endPoint.y) || (minSize.height && minSize.width);
}

/*****************************************************************************/

void ShapeDrawStrategy::reshape (IClutterActor *a)
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
