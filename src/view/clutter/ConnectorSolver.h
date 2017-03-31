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
        static primitives::PointVector solve (primitives::Ray const &a, primitives::Ray const &b);

private:
        static primitives::Point advance (primitives::Point const &point, Direction dir, float length);
        static float distance (primitives::Point const &a, primitives::Point const &b, Direction dir);
        static primitives::Ray rayPerpendicular (primitives::Ray const &perpendicularTo, primitives::Point const &towardsPoint, primitives::Point const &startPoint);
};

#endif // CONNECTORSOLVER_H
