/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedLineConnectorStrategy.h"
#include "view/Port.h"
#include <core/Core.h>
#include <view/INodeView.h>

void DashedLineConnectorStrategy::onButtonPress (Event const &e)
{
        startPoint = e.positionParentCoords;
        endPoint = Point ();

        startObject = e.object;
        endObject = nullptr;

        line->setPointA (e.positionStageCoords);
        line->setPointB (e.positionStageCoords);

        AbstractConnector *lc;
        if ((lc = dynamic_cast<AbstractConnector *> (line))) {
                Port *pa = dynamic_cast<Port *> (startObject);

                if (pa) {
                        lc->setAFacing (pa->getFacing ());
                        lc->setBFacing (getOppositeDirection (pa->getFacing ()));
                }
        }

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

        /*****************************************************************************/
        /* Connect flow::INodes                                                      */
        /*****************************************************************************/

        assert (lc->getArc ());
        flow::Arc *arc = lc->getArc ().get ();

        //        assert (pa->nodeView);
        //        assert (pa->nodeView->getNode ());

        if (pa->nodeView && pa->nodeView->getNode ()) {
                flow::INode *startNode = pa->nodeView->getNode ().get ();

                if (pa->isInput ()) {
                        startNode->setInput (pa->number, arc);
                }
                else {
                        startNode->addOutput (pa->number, arc);
                }
        }

        //        assert (pb->nodeView);
        //        assert (pb->nodeView->getNode ());

        if (pb->nodeView && pb->nodeView->getNode ()) {
                flow::INode *endNode = pb->nodeView->getNode ().get ();

                if (pb->isInput ()) {
                        endNode->setInput (pb->number, arc);
                }
                else {
                        endNode->addOutput (pb->number, arc);
                }
        }
}
