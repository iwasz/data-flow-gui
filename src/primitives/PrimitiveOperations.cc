///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/

//#include "PrimitiveOperations.h"
//#include <cmath>

//namespace primitives {

///**
// * Move point "point" according direction dir (always horizontally or vertically)
// * by length.
// */
//Point advance (Point const &point, Direction dir, float length)
//{
//        Point p = point;

//        switch (dir) {
//        case NORTH:
//                p.y -= length;
//                break;

//        case SOUTH:
//                p.y += length;
//                break;

//        case EAST:
//                p.x += length;
//                break;

//        case WEST:
//                p.x -= length;
//                break;

//        case NONE:
//        default:
//                break;
//        }

//        return p;
//}

///**
// * Distance between two points a and b, but according to direction dir, so
// * if dir is N or S it returns dinstance between Y coordinates, and when dir
// * is E or W, between X coordinates.
// */
//float distance (Point const &a, Point const &b, Direction dir)
//{
//        if (dir == NORTH || dir == SOUTH) {
//                return fabs (a.y - b.y);
//        }
//        else if (dir == EAST || dir == WEST) {
//                return fabs (a.x - b.x);
//        }

//        return 0;
//}

//Ray rayPerpendicular (Ray const &perpendicularTo, Point const &towardsPoint, Point const &startPoint)
//{
//        Direction ld;

//        if (perpendicularTo.isVertical ()) {
//                ld = (towardsPoint.x > perpendicularTo.getA ().x) ? (EAST) : (WEST);
//        }
//        else {
//                ld = (towardsPoint.y > perpendicularTo.getA ().y) ? (SOUTH) : (NORTH);
//        }

//        return Ray (startPoint, ld);
//}

//} // namespace
