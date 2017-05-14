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
        //                router.setRoutingOption ();
        //                                router.setRoutingParameter ();
        router.setRoutingPenalty (Avoid::RoutingParameter::segmentPenalty, 1);
}
