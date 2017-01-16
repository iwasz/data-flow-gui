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
        setCppImplementation ();
}

/*****************************************************************************/

void Line::setPointA (Point const &p) { iw_line_set_point_a (IW_LINE (self), p.x, p.y); }

/*****************************************************************************/

Point Line::getPointA () const
{
        Point p;
        iw_line_get_point_a (IW_LINE (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

void Line::setPointB (Point const &p) { iw_line_set_point_b (IW_LINE (self), p.x, p.y); }

/*****************************************************************************/

Point Line::getPointB () const
{
        Point p;
        iw_line_get_point_a (IW_LINE (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

float Line::getStrokeWidth () const { return iw_line_get_stroke_width (IW_LINE (self)); }

/*****************************************************************************/

void Line::setStrokeWidth (float value) { iw_line_set_stroke_width (IW_LINE (self), value); }

/*****************************************************************************/

float Line::getStrokeDash () const { return iw_line_get_stroke_dash (IW_LINE (self)); }

/*****************************************************************************/

void Line::setStrokeDash (float value) { iw_line_set_stroke_dash (IW_LINE (self), value); }

/*****************************************************************************/

Color Line::getStrokeColor () const { return Color (iw_line_get_stroke_color (IW_LINE (self))); }

/*****************************************************************************/

void Line::setStrokeColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_line_set_stroke_color (IW_LINE (self), &color);
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

Color Line::getFontColor () const
{
        ClutterColor c;
        iw_line_get_font_color (IW_LINE (self), &c);
        return Color (&c);
}

/*****************************************************************************/

void Line::setFontColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_line_set_font_color (IW_LINE (self), &color);
}

/*****************************************************************************/

bool Line::isTextEditable () const { return iw_line_is_editable (IW_LINE (self)); }

/*****************************************************************************/

void Line::setTextEditable (bool b) { iw_line_set_editable (IW_LINE (self), b); }
