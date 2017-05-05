/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Line.h"
#include "clutter/iw_line.h"
#include <core/Exception.h>

Line::Line ()
{
        self = iw_line_new ();
        clutter_actor_set_reactive (self, TRUE);
        iw_actor_set_user_data (IW_ACTOR (self), this);
        setCppImplementation ();
}

/*****************************************************************************/

void Line::setPointA (primitives::Point const &p) { iw_line_set_point_a (IW_LINE (self), p.x, p.y); }

/*****************************************************************************/

primitives::Point Line::getPointA () const
{
        primitives::Point p;
        iw_line_get_point_a (IW_LINE (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

void Line::setPointB (primitives::Point const &p) { iw_line_set_point_b (IW_LINE (self), p.x, p.y); }

/*****************************************************************************/

primitives::Point Line::getPointB () const
{
        primitives::Point p;
        iw_line_get_point_a (IW_LINE (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

std::string Line::getText () const { return iw_line_get_text (IW_LINE (self)); }

/*****************************************************************************/

void Line::setText (std::string const t) { iw_line_set_text (IW_LINE (self), t.c_str ()); }

/*****************************************************************************/

std::string Line::getFont () const { return iw_line_get_font (IW_LINE (self)); }

/*****************************************************************************/

void Line::setFont (std::string const t) { iw_line_set_font (IW_LINE (self), t.c_str ()); }

/*****************************************************************************/

primitives::Color Line::getFontColor () const
{
        ClutterColor c;
        iw_line_get_font_color (IW_LINE (self), &c);
        return primitives::Color (&c);
}

/*****************************************************************************/

void Line::setFontColor (const primitives::Color &value)
{
        ClutterColor color = primitives::Color::toClutterColor (value);
        iw_line_set_font_color (IW_LINE (self), &color);
}

/*****************************************************************************/

bool Line::isTextEditable () const { return iw_line_is_editable (IW_LINE (self)); }

/*****************************************************************************/

void Line::setTextEditable (bool b) { iw_line_set_editable (IW_LINE (self), b); }
