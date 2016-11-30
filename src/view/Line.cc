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

        ClutterAction *dragAction = clutter_drag_action_new ();
        clutter_actor_add_action (self, dragAction);
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

std::string Line::getStrokeColor () const
{
        ClutterColor *color = iw_line_get_stroke_color (IW_LINE (self));
        return std::string (clutter_color_to_string (color));
}

/*****************************************************************************/

void Line::setStrokeColor (const std::string &value)
{
        ClutterColor color;

        if (!clutter_color_from_string (&color, value.c_str ())) {
                throw Core::Exception ("Wrong color string [" + value + "].");
        }

        iw_line_set_stroke_color (IW_LINE (self), &color);
}
