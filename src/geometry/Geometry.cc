/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Geometry.h"

Dimension operator- (Point const &a, Point const &b)
{
        return Dimension (a.x - b.x, a.y - b.y);
}


