/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Geometry.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <core/Exception.h>
#include <ostream>

/*****************************************************************************/

std::ostream &operator<< (std::ostream &o, Point const &p)
{
        o << "[" << p.x << ", " << p.y << "]";
        return o;
}

/*****************************************************************************/

Point::Point (std::string const &s)
{
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        tokenizer tok (s, boost::char_separator<char> (","));
        tokenizer::iterator i = tok.begin ();

        assertThrow (i != tok.end (), "Point::Point : problem parsing x coordinate string : [" + s + "]");
        x = boost::lexical_cast<float> (boost::trim_copy (*i++));

        assertThrow (i != tok.end (), "Point::Point : problem parsing y coordinate string : [" + s + "]");
        y = boost::lexical_cast<float> (boost::trim_copy (*i));
}

/*****************************************************************************/

Dimension::Dimension (std::string const &s)
{
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        tokenizer tok (s, boost::char_separator<char> (","));
        tokenizer::iterator i = tok.begin ();

        assertThrow (i != tok.end (), "Dimension::Dimension : problem parsing width string : [" + s + "]");
        width = boost::lexical_cast<float> (boost::trim_copy (*i++));

        assertThrow (i != tok.end (), "Dimension::Dimension : problem parsing height string : [" + s + "]");
        height = boost::lexical_cast<float> (boost::trim_copy (*i));
}

/*****************************************************************************/

Dimension operator- (Point const &a, Point const &b) { return Dimension (a.x - b.x, a.y - b.y); }
bool operator== (Point const &a, Point const &b) { return a.x == b.x && a.y == b.y; }

/*****************************************************************************/

Dimension Box::getDimension () const { return Dimension (std::abs (a.x - b.x), std::abs (a.y - b.y)); }

/*****************************************************************************/

bool Box::isInside (Box const &box) const
{
        // a inside b
        float aax = std::min (a.x, b.x);
        float aay = std::min (a.y, b.y);
        float abx = std::max (a.x, b.x);
        float aby = std::max (a.y, b.y);

        float bax = std::min (box.a.x, box.b.x);
        float bay = std::min (box.a.y, box.b.y);
        float bbx = std::max (box.a.x, box.b.x);
        float bby = std::max (box.a.y, box.b.y);

        return aax >= bax && abx <= bbx && aay >= bay && aby <= bby;
}

/*****************************************************************************/

bool Box::isIntersects (const Box &box) const
{

        if (b.x < box.a.x) {
                return false;
        }
        if (a.x > box.b.x) {
                return false;
        }
        if (b.y < box.a.y) {
                return false;
        }
        if (a.y > box.b.y) {
                return false;
        }

        return true;
}

/*****************************************************************************/

void Box::resizeContain (Box const &box)
{
        if (getDimension () == Dimension ()) {
                *this = box;
        }

        // Assuming a.x < b.x && a.y < b.y in *this and box:
        a.x = std::min (a.x, box.a.x);
        a.y = std::min (a.y, box.a.y);
        b.x = std::max (b.x, box.b.x);
        b.y = std::max (b.y, box.b.y);
}

/*****************************************************************************/

void Box::sort ()
{
        float minX = std::min (a.x, b.x);
        float maxX = std::max (a.x, b.x);
        float minY = std::min (a.y, b.y);
        float maxY = std::max (a.y, b.y);
        a.x = minX;
        a.y = minY;
        b.x = maxX;
        b.y = maxY;
}
