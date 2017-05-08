/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedLineConnectorStrategy.h"
#include "view/Port.h"
#include "view/SceneAPI.h"
#include <core/Core.h>
#include <view/INodeView.h>

void DashedLineConnectorStrategy::onButtonPress (Event const &e)
{
        startPoint = e.positionParentCoords;
        endPoint = primitives::Point ();

        startObject = e.object;
        endObject = nullptr;

        line->setPointA (e.positionStageCoords);
        line->setPointB (e.positionStageCoords);

        //        IConnector *lc;
        //        if ((lc = dynamic_cast<IConnector *> (line))) {
        //                Port *pa = dynamic_cast<Port *> (startObject);

        //                if (pa) {
        //                        lc->setAFacing (pa->getFacing ());
        //                        lc->setBFacing (getOppositeDirection (pa->getFacing ()));
        //                }
        //        }

        line->setVisible (true);
}

/*****************************************************************************/

void DashedLineConnectorStrategy::onMotion (const Event &e) { line->setPointB (e.positionStageCoords); }

/*****************************************************************************/

bool DashedLineConnectorStrategy::onButtonRelease (const Event &e)
{
        line->setVisible (false);
        endPoint = e.positionParentCoords;
        endObject = e.object;
        return startPoint.x != endPoint.x || startPoint.y != endPoint.y;
}

/*****************************************************************************/

void DashedLineConnectorStrategy::onObjectCreated (IClutterActor *a)
{
        IConnector *lc = dynamic_cast<IConnector *> (a);

        if (!lc) {
                throw Core::Exception ("DashedLineStrategy::reshape could not cast actor to Line *");
        }

//        lc->setPointA (startPoint);
//        lc->setPointB (endPoint);

        Port *pa = dynamic_cast<Port *> (startObject);
        Port *pb = dynamic_cast<Port *> (endObject);

        SceneAPI::connect (lc, pa, pb);
}
