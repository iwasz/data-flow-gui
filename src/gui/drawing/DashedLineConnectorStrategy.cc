/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedLineConnectorStrategy.h"
#include "view/Port.h"

void DashedLineConnectorStrategy::onButtonPress (Point p, Object *o)
{
        startPoint = p;
        endPoint = Point ();

        startObject = o;
        endObject = nullptr;

        line->setPointA (startPoint);
        line->setPointB (startPoint);
        line->setVisible (true);
}

/*****************************************************************************/

void DashedLineConnectorStrategy::onMotion (Point p, Object *o) { line->setPointB (p); }

/*****************************************************************************/

bool DashedLineConnectorStrategy::onButtonRelease (Point p, Object *o)
{
        line->setVisible (false);
        endPoint = p;
        endObject = o;
        return startPoint.x != endPoint.x || startPoint.y != endPoint.y;
}

/*****************************************************************************/

void DashedLineConnectorStrategy::reshape (IClutterActor *a)
{
        LineConnector *lc = dynamic_cast<LineConnector *> (a);

        if (!lc) {
                throw Core::Exception ("DashedLineStrategy::reshape could not cast actor to Line *");
        }

        lc->setPointA (startPoint);
        lc->setPointB (endPoint);

        Port *pa = dynamic_cast<Port *> (startObject);
        Port *pb = dynamic_cast<Port *> (endObject);

        if (!pa || !pb) {
                return;
        }

        lc->connect (&pa->anchor, IConnector::A);
        lc->connect (&pb->anchor, IConnector::B);
}