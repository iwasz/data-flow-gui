/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GEMETRY_LINE_H
#define GEMETRY_LINE_H

#include "Geometry.h"

class Line {
public:
        Line (Point const &a, Point const &b) : a (a), b (b) {}
        virtual ~Line () {}

        virtual Point getA () const { return a; }
        virtual void setA (Point const &p) { a = p; }

        virtual Point getB () const { return b; }
        virtual void setB (Point const &p) { b = p; }

protected:
        Point a;
        Point b;
};

#endif // LINE_H
