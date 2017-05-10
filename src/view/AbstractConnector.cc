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
        IClutterActor *actor = dynamic_cast<IClutterActor *> (this);

        // TODO dirty hack!
        if (!connRef) {
                connRef = new Avoid::ConnRef (actor->getRouter ());
                connRef->setCallback (&AbstractConnector::onRerouteCallback, this);
        }

        Avoid::ConnEnd newSrcPt (port->getShapeRef (), port->getViewNumber () + 1);

        if (s == Side::A) {
                connRef->setSourceEndpoint (newSrcPt);
                a = port;
        }
        else {
                connRef->setDestEndpoint (newSrcPt);
                b = port;
        }
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
        // TODO
        a = b = nullptr;
}
