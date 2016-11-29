/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Circle.h"
#include "clutter/iw_circle.h"
#include <core/Exception.h>

/*****************************************************************************/

Circle::Circle ()
{
        self = iw_circle_new ();
        clutter_actor_set_reactive (self, TRUE);

        ClutterAction *dragAction = clutter_drag_action_new ();
        clutter_actor_add_action (self, dragAction);
}

/*****************************************************************************/

bool Circle::isFill () const { return iw_circle_is_fill (IW_CIRCLE (self)); }

/*****************************************************************************/

void Circle::setFill (bool value) { iw_circle_set_fill (IW_CIRCLE (self), value); }

/*****************************************************************************/

float Circle::getStrokeWidth () const { return iw_circle_get_stroke_width (IW_CIRCLE (self)); }

/*****************************************************************************/

void Circle::setStrokeWidth (float value) { iw_circle_set_stroke_width (IW_CIRCLE (self), value); }

/*****************************************************************************/

float Circle::getStrokeDash () const { return iw_circle_get_stroke_dash (IW_CIRCLE (self)); }

/*****************************************************************************/

void Circle::setStrokeDash (float value) { iw_circle_set_stroke_dash (IW_CIRCLE (self), value); }

/*****************************************************************************/

std::string Circle::getStrokeColor () const
{
        ClutterColor *color = iw_circle_get_stroke_color (IW_CIRCLE (self));
        return std::string (clutter_color_to_string (color));
}

/*****************************************************************************/

void Circle::setStrokeColor (const std::string &value)
{
        ClutterColor color;

        if (!clutter_color_from_string (&color, value.c_str ())) {
                throw Core::Exception ("Wrong color string [" + value + "].");
        }

        iw_circle_set_stroke_color (IW_CIRCLE (self), &color);
}

/*****************************************************************************/

std::string Circle::getFillColor () const
{
        ClutterColor *color = iw_circle_get_fill_color (IW_CIRCLE (self));
        return std::string (clutter_color_to_string (color));
}

/*****************************************************************************/

void Circle::setFillColor (const std::string &value)
{
        ClutterColor color;

        if (!clutter_color_from_string (&color, value.c_str ())) {
                throw Core::Exception ("Wrong color string [" + value + "].");
        }

        iw_circle_set_fill_color (IW_CIRCLE (self), &color);
}
