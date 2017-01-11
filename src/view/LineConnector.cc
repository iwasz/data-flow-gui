/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LineConnector.h"

void LineConnector::onMoveAnchor (float x, float y, Side s)
{
        if (s == A) {
                setPointA (Point (x, y));
        }
        else {
                setPointB (Point (x, y));
        }
}
