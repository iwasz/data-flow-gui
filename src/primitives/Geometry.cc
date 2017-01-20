/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Geometry.h"
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <core/Exception.h>

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
