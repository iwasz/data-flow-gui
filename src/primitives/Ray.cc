///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/

//#include "Ray.h"
//#include <cmath>
//#include <limits>

//namespace primitives {

//Ray::Ray (Point const &a, Direction d) : Line (a, Point ()), dir (d)
//{
//        switch (dir) {
//        case NORTH:
//                b.x = a.x;
//                b.y = -std::numeric_limits<float>::infinity ();
//                break;

//        case SOUTH:
//                b.x = a.x;
//                b.y = std::numeric_limits<float>::infinity ();
//                break;

//        case EAST:
//                b.x = std::numeric_limits<float>::infinity ();
//                b.y = a.y;
//                break;

//        case WEST:
//                b.x = -std::numeric_limits<float>::infinity ();
//                b.y = a.y;
//                break;

//        case NONE:
//        default:
//                break;
//        }
//}

///*****************************************************************************/

//bool Ray::isOppositeDirection (Ray const &b) const
//{
//        // Only rays facing eachother will be taken into account.
//        return (getDirection () == getOppositeDirection (b.getDirection ()));
//}

///*****************************************************************************/

//bool Ray::isFacing (Ray const &b) const
//{
//        if (!isOppositeDirection (b)) {
//                return false;
//        }

//        if ((getDirection () == NORTH && getA ().y < b.getA ().y) || (getDirection () == SOUTH && getA ().y > b.getA ().y)
//            || (getDirection () == EAST && getA ().x > b.getA ().x) || (getDirection () == WEST && getA ().x < b.getA ().x)) {
//                return false;
//        }

//        return true;
//}

///*****************************************************************************/

//Point Ray::isConnection (Ray const &b) const
//{
//        if (!isFacing (b)) {
//                return INVALID_POINT;
//        }

//        Point p;

//        // If vertical
//        if (isVertical ()) {
//                if (round (getA ().x) == round (b.getA ().x)) {
//                        p.x = getA ().x;
//                        p.y = fabs (getA ().y - b.getA ().y) / 2.0;
//                        return p;
//                }
//        }
//        else if (isHorizontal ()) {
//                if (round (getA ().y) == round (b.getA ().y)) {
//                        p.x = fabs (getA ().x - b.getA ().x) / 2.0;
//                        p.y = getA ().y;
//                        return p;
//                }
//        }

//        return INVALID_POINT;
//}

///*****************************************************************************/

//Point Ray::isCrossing (Ray const &b) const
//{
//        if (!isPerpendicularTo (b)) {
//                return INVALID_POINT;
//        }

//        float aax = getA ().x;
//        float aay = getA ().y;
//        float abx = getB ().x;
//        float aby = getB ().y;
//        float bax = b.getA ().x;
//        float bay = b.getA ().y;
//        float bbx = b.getB ().x;
//        float bby = b.getB ().y;

//        // Normalised coordinates of horizontal ray. Point A is on the left, point B is on the right.
//        float hax, hay, hbx, hby;
//        // Normalised coordinates of vertical ray. Point A is on the top, point B is on the bottom.
//        float vax, vay, vbx, vby;

//        if (isVertical ()) {
//                vax = aax;
//                vay = fmin (aay, aby);
//                vbx = aax;
//                vby = fmax (aay, aby);
//        }
//        else {
//                hax = fmin (aax, abx);
//                hay = aay;
//                hbx = fmax (aax, abx);
//                hby = aay;
//        }

//        if (isHorizontal ()) {
//                vax = bax;
//                vay = fmin (bay, bby);
//                vbx = bax;
//                vby = fmax (bay, bby);
//        }
//        else {
//                hax = fmin (bax, bbx);
//                hay = bay;
//                hbx = fmax (bax, bbx);
//                hby = bay;
//        }

//        if ((hay >= vay && hay <= vby) && (vax >= hax && vax <= hbx)) {
//                return Point (vax, hay);
//        }

//        return INVALID_POINT;
//}

//} // namespace
