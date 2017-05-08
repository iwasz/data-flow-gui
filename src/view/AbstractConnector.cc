/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractConnector.h"
#include "IClutterActor.h"

// AbstractConnector::AbstractConnector ()
//{
//        // TODO get rid of this cast
//        IClutterActor *a = dynamic_cast<IClutterActor *> (this);
//        connRef = new Avoid::ConnRef (a->getRouter ());
//}

/*****************************************************************************/

void AbstractConnector::connect (Port *port, Side s)
{
        // TODO get rid of this cast
        IClutterActor *a = dynamic_cast<IClutterActor *> (this);

        // TODO dirty hack!
        if (!connRef) {
                connRef = new Avoid::ConnRef (a->getRouter ());
                connRef->setCallback (&AbstractConnector::onRerouteCallback, this);
        }

        Avoid::ConnEnd newSrcPt (port->getShapeRef (), port->getViewNumber () + 1);

        if (s == Side::A) {
                connRef->setSourceEndpoint (newSrcPt);
        }
        else {
                connRef->setDestEndpoint (newSrcPt);
        }

//        const Avoid::PolyLine route = connRef->displayRoute ();
//        for (size_t i = 0; i < route.size (); ++i) {
//                Avoid::Point point = route.at (i);
//                printf ("%f, %f\n", point.x, point.y);
//        }

        /*---------------------------------------------------------------------------*/

        //        an->connect (this, s);
        //        if (s == A) {
        //                a = an;
        ////                setAFacing (a->getFacing ());
        //        }
        //        else {
        //                b = an;
        ////                setBFacing (b->getFacing ());
        //        }

        //        onConnectAnchor (an->getPosition (), s);
}

/*****************************************************************************/

void AbstractConnector::onRerouteCallback (void *v)
{
        AbstractConnector *ac = static_cast<AbstractConnector *> (v);
        ac->onReroute (ac->connRef);
}

/*****************************************************************************/
void AbstractConnector::disconnect (/*Side s*/)
{
        //        a->disconnect (this, A);
        //        if (s == A) {
        //                a = nullptr;
        //        }
        //                onDisconnectAnchor (a->getPosition (), s);
        //        else {
        //                b = nullptr;
        //                onDisconnectAnchor (b->getPosition (), s);
        //        }

        //        setAFacing (NONE);
        //        setBFacing (NONE);
        a->disconnect (this);
        b->disconnect (this);
        a = nullptr;
        b = nullptr;
        //        onDisconnectAnchor (/*a->getPosition (), s*/);
}
