/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GEOMETRY_DF_POINT_H
#define GEOMETRY_DF_POINT_H

#include <ReflectionParserAnnotation.h>
#include <limits>
#include <string>
#include <vector>

struct __tiliae_reflect__ Point {
        Point () : x (0), y (0) {}
        Point (float x, float y) : x (x), y (y) {}
        Point (std::string const &s);

        bool isValid () const { return x != std::numeric_limits<float>::infinity () && y != std::numeric_limits<float>::infinity (); }
        operator bool() const { return isValid (); }

        float x;
        float y;
};

const Point INVALID_POINT = Point (std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity ());

extern std::ostream &operator<< (std::ostream &o, Point const &p);

typedef std::vector<Point> PointVector;

struct __tiliae_reflect__ Dimension {
        Dimension () : width (0), height (0) {}
        Dimension (float w, float h) : width (w), height (h) {}
        Dimension (std::string const &s);
        bool operator== (Dimension const &d) const { return width == d.width && height == d.height; }
        bool operator!= (Dimension const &d) const { return width != d.width || height != d.height; }

        float width;
        float height;
};

extern Dimension operator- (Point const &a, Point const &b);
extern bool operator== (Point const &a, Point const &b);

struct Box {
        Box () {}
        Box (Point const &a, Point const &b) : a (a), b (b) { sort (); }
        Box (Point const &a, Dimension const &d) : a (a), b (a.x + d.width, a.y + d.height) { sort (); }

        Dimension getDimension () const;
        /// a.isInside (b) tells if a is inside b. Read as in English.
        bool isInside (Box const &box) const;
        /// a.isIntersects (b) tells if a overlaps with b and vice versa, so order is not relevant.
        bool isIntersects (Box const &box) const;
        /// Resize this, so it could enclose box, and the space between the two.
        void resizeContain (Box const &box);

        Point getA () const { return a; }

        void setA (const Point &value)
        {
                a = value;
                sort ();
        }

        Point getB () const { return b; }

        void setB (const Point &value)
        {
                b = value;
                sort ();
        }

private:
        void sort ();

        Point a;
        Point b;
};

#endif // POINT_H
