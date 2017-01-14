/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LineConnector.h"

LineConnector::LineConnector () : Line (), AbstractConnector () {}

void LineConnector::onMoveAnchor (const Point &p, Side s)
{
        if (s == A) {
                setPointA (p);
        }
        else {
                setPointB (p);
        }
}
