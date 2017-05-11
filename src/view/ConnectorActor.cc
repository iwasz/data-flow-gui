/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ConnectorActor.h"
#include "Port.h"

void ConnectorActor::connect (Port *port, Side s)
{
        getRoutable ()->connect (port->getRoutablePin (), s);

        //        // TODO get rid of this cast
        //        IClutterActor *actor = dynamic_cast<IClutterActor *> (this);

        //        // TODO dirty hack!
        //        if (!connRef) {
        //                connRef = new Avoid::ConnRef (actor->getRouter ());
        //                connRef->setCallback (&AbstractConnector::onRerouteCallback, this);
        //        }

        //        Avoid::ConnEnd newSrcPt (port->getShapeRef (), port->getViewNumber () + 1);

        //        if (s == Side::A) {
        //                connRef->setSourceEndpoint (newSrcPt);
        //                a = port;
        //        }
        //        else {
        //                connRef->setDestEndpoint (newSrcPt);
        //                b = port;
        //        }
}

/*****************************************************************************/

void ConnectorActor::disconnect (/*Side s*/)
{
        // TODO
        a = b = nullptr;
}
