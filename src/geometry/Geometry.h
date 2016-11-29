/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GEOMETRY_DF_POINT_H
#define GEOMETRY_DF_POINT_H

struct Point {
        Point () : x (0), y (0) {}
        Point (float x, float y) : x (x), y (y) {}
        float x;
        float y;
};

struct Dimension {
        Dimension () : width (0), height (0) {}
        Dimension (float w, float h) : width (w), height (h) {}
        float width;
        float height;
};

extern Dimension operator- (Point const &a, Point const &b);

#endif // POINT_H
