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

void Port::createPin ()
{
        // TODO this cast is bad, API is bad if cast is needed.
        IClutterActor *a = dynamic_cast<IClutterActor *> (getNodeView ());
        // TODO cope with this "+1". libavoid wont let you set 0 there.
        pin = new Avoid::ShapeConnectionPin (a->getShapeRef (), getViewNumber () + 1, 0, 0, false, 0, Avoid::ConnDirRight);
}

Avoid::ShapeRef *Port::getShapeRef ()
{
        if (!getNodeView ()) {
                return nullptr;
        }

        // TODO this cast is bad, API is bad if cast is needed.
        IClutterActor *a = dynamic_cast<IClutterActor *> (getNodeView ());
        return a->getShapeRef ();
}
