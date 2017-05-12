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

//void Port::reposition () { routablePin->setPosition (getPosition ()); }

/*****************************************************************************/

primitives::Point Port::getPosition () const { return nodeActor->getPortPosition (this); }
