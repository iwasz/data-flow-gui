/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ConnectorRoutable.h"
#include "RoutablePin.h"

void ConnectorRoutable::init (primitives::Point const &p, primitives::Dimension const &d0, IRoutableObserver *o)
{
        setObserver (o);

        if (!getRouter ()) {
                return;
        }

        if (!connRef) {
                connRef = new Avoid::ConnRef (getRouter ());
                connRef->setCallback (&ConnectorRoutable::onRerouteCallback, this);
        }
}

/*****************************************************************************/

void ConnectorRoutable::onRerouteCallback (void *v)
{
        ConnectorRoutable *cr = static_cast<ConnectorRoutable *> (v);

        if (cr->getObserver ()) {
                cr->getObserver ()->onReroute (cr->connRef);
        }
}

/*****************************************************************************/

void ConnectorRoutable::connect (RoutablePin *pin, Side s)
{
        Avoid::ConnEnd newSrcPt (pin->getShapeRef (), pin->getClassNumber ());

        if (s == Side::A) {
                connRef->setSourceEndpoint (newSrcPt);
        }
        else {
                connRef->setDestEndpoint (newSrcPt);
        }
}
