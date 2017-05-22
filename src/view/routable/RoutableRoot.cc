/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RoutableRoot.h"

RoutableRoot::RoutableRoot () : router (Avoid::PolyLineRouting)
{
        router.setRoutingPenalty (Avoid::RoutingParameter::segmentPenalty, 1);
        router.setRoutingOption (Avoid::nudgeOrthogonalSegmentsConnectedToShapes, true);
        router.setRoutingOption (Avoid::nudgeOrthogonalTouchingColinearSegments, true);
//        router.setRoutingParameter (Avoid::shapeBufferDistance, 30);
}
