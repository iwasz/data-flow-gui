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

void DashedLineConnectorStrategy::onObjectCreated (IClutterActor *a)
{
        LineConnector *lc = dynamic_cast<LineConnector *> (a);

        if (!lc) {
                throw Core::Exception ("DashedLineStrategy::reshape could not cast actor to Line *");
        }

        /*
         * Move to bottom. I don't want this to be separate method of AbstractActor to preven polution.
         * TODO Moving to bottom somehow decreases refresh rate when moving nodes around. It can be seen that
         * connector moves slower than the node it is connected to.
         */
        ClutterActor *parent = clutter_actor_get_parent (lc->getActor ());
        clutter_actor_set_child_below_sibling (parent, lc->getActor (), nullptr);

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

        assert (pa->nodeView);
        assert (pa->nodeView->getNode ());
        flow::INode *startNode = pa->nodeView->getNode ().get ();

        assert (pb->nodeView);
        assert (pb->nodeView->getNode ());
        flow::INode *endNode = pb->nodeView->getNode ().get ();

        if (pa->isInput ()) {
                startNode->setInput (pa->number, arc);
        }
        else {
                startNode->addOutput (pa->number, arc);
        }

        if (pb->isInput ()) {
                endNode->setInput (pb->number, arc);
        }
        else {
                endNode->addOutput (pb->number, arc);
        }

#if 0
        flow::Program program;

        flow::Copy c2;
        flow::Copy c1;
        flow::Add a;
        flow::Console l;

        program.addNode (&l);
        program.addNode (&c1);
        program.addNode (&a);
        program.addNode (&c2);

        // c2 górne
        flow::Arc a1 (0);
        c2.addOutput (0, &a1);

        // c1 dolne
        flow::Arc a2 (1);
        flow::Arc a3 (1);
        c1.addOutput (0, &a3);
        c1.addOutput (0, &a2);

        // add
        flow::Arc a4;
        flow::Arc a5 (1);
        a.addOutput (0, &a4);
        a.addOutput (0, &a5);

        c1.setInput (0, &a4);
        c2.setInput (0, &a2);
        a.setInput (0, &a1);
        a.setInput (1, &a3);
        l.setInput (0, &a5);

        program.run ();
#endif
}
