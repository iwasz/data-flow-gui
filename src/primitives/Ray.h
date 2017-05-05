/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GEOMETRY_RAY_H
#define GEOMETRY_RAY_H

#include "primitives/Direction.h"
#include "primitives/Line.h"

namespace primitives {

class Ray : public Line {
public:
        Ray (Point const &a, Direction d);
        virtual ~Ray () {}

        virtual Point getA () const { return a; }
        virtual void setA (Point const &p) { a = p; }

        virtual Point getB () const { return b; }
        Direction getDirection () const { return dir; }

        bool isVertical () const { return dir == NORTH || dir == SOUTH; }
        bool isHorizontal () const { return dir == WEST || dir == EAST; }
        bool isPerpendicularTo (Ray const &b) const { return (isVertical () && b.isHorizontal ()) || (isHorizontal () && b.isVertical ()); }
        bool isParallelTo (Ray const &b) const { return (isVertical () && b.isVertical ()) || (isHorizontal () && b.isHorizontal ()); }
        bool isOppositeDirection (Ray const &b) const;
        bool isFacing (Ray const &b) const;

        /// Returns if two rays facing each other connects, and returns point of connection in the middle or INVALID_POINT.
        Point isConnection (Ray const &b) const;

        /// Returns if two perpendicullar rays cross (at right angle).
        Point isCrossing (Ray const &b) const;

        bool operator== (Ray const &r) const { return r.dir == dir && r.getA () == getA (); }

private:
        void setB (Point const &p) {}

protected:
        Direction dir;
};

} // namespace

#endif // RAY_H
