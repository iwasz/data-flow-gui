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

Circle::Circle ()
{
        self = iw_circle_new ();
        clutter_actor_set_reactive (self, TRUE);

        ClutterAction *dragAction = clutter_drag_action_new ();
        clutter_actor_add_action (self, dragAction);
        clutter_actor_show (self);
}

void Circle::setParent (IClutterActor *parent) { clutter_actor_add_child (parent->getActor (), self); }

bool Circle::getVisible () const { return clutter_actor_is_visible (self); }

void Circle::setVisible (bool value)
{
        if (value) {
                clutter_actor_show (self);
        }
        else {
                clutter_actor_hide (self);
        }
}

bool Circle::isFill () const { return iw_circle_is_fill (IW_CIRCLE (self)); }

void Circle::setFill (bool value) { iw_circle_set_fill (IW_CIRCLE (self), value); }

float Circle::getH () const { return clutter_actor_get_height (self); }

void Circle::setH (float h) { clutter_actor_set_height (self, h); }

float Circle::getW () const { return clutter_actor_get_width (self); }

void Circle::setW (float w) { clutter_actor_set_width (self, w); }

float Circle::getY () const { return clutter_actor_get_y (self); }

void Circle::setY (float y) { clutter_actor_set_y (self, y); }

float Circle::getX () const { return clutter_actor_get_x (self); }

void Circle::setX (float x) { clutter_actor_set_x (self, x); }

float Circle::getStrokeWidth () const { return iw_circle_get_stroke_width (IW_CIRCLE (self)); }

void Circle::setStrokeWidth (float value) { iw_circle_set_stroke_width (IW_CIRCLE (self), value); }

float Circle::getStrokeDash () const { return iw_circle_get_stroke_dash (IW_CIRCLE (self)); }

void Circle::setStrokeDash (float value) { iw_circle_set_stroke_dash (IW_CIRCLE (self), value); }

std::string Circle::getStrokeColor () const
{
        ClutterColor *color = iw_circle_get_stroke_color (IW_CIRCLE (self));
        return std::string (clutter_color_to_string (color));
}

void Circle::setStrokeColor (const std::string &value)
{
        ClutterColor color;

        if (!clutter_color_from_string (&color, value.c_str ())) {
                throw Core::Exception ("Wrong color string [" + value + "].");
        }

        iw_circle_set_stroke_color (IW_CIRCLE (self), &color);
}

std::string Circle::getFillColor () const
{
        ClutterColor *color = iw_circle_get_fill_color (IW_CIRCLE (self));
        return std::string (clutter_color_to_string (color));
}

void Circle::setFillColor (const std::string &value)
{
        ClutterColor color;

        if (!clutter_color_from_string (&color, value.c_str ())) {
                throw Core::Exception ("Wrong color string [" + value + "].");
        }

        iw_circle_set_fill_color (IW_CIRCLE (self), &color);
}
