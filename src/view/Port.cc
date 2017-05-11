/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Port.h"
#include "IClutterActor.h"
#include "INodeView.h"
#include "NodeActor.h"
#include "routable/RoutablePin.h"

/*****************************************************************************/

void Port::init ()
{
        if (routablePin && nodeActor) {
                routablePin->init (getPosition (), nodeActor->getRoutable ());
        }
}

/*****************************************************************************/

void RoutablePin::init (primitives::Point const &p, IRoutable *owner)
{
        assert (owner);
        pin = new Avoid::ShapeConnectionPin (owner->getShapeRef (), getClassNumber (), p.x, p.y, false, 0, Avoid::ConnDirAll);
}

/*****************************************************************************/

primitives::Point Port::getPosition () const { return nodeActor->getPortPosition (this); }
