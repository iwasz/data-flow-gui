/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONNECTORSOLVER_H
#define CONNECTORSOLVER_H

#include "primitives/Direction.h"
#include "primitives/Geometry.h"
#include "primitives/Ray.h"

/**
 * Class forcomputing a shape of segmented connector connecting 2 points like
 * in Libre Office draw or Visio. Implementing this was way, way harder than I
 * expected :(
 */
class ConnectorSolver {
public:
        static PointVector solve (Ray const &a, Ray const &b);

private:
        static Point advance (Point const &point, Direction dir, float length);
        static float distance (Point const &a, Point const &b, Direction dir);
        static Ray rayPerpendicular (Ray const &perpendicularTo, Point const &towardsPoint, Point const &startPoint);
};

#endif // CONNECTORSOLVER_H
