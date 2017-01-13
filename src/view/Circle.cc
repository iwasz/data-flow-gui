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
//        ClutterAction *dragAction = clutter_drag_action_new ();
//        clutter_actor_add_action (self, dragAction);
        setCppImplementation ();
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

Color Circle::getStrokeColor () const { return Color (iw_circle_get_stroke_color (IW_CIRCLE (self))); }

/*****************************************************************************/

Color Circle::getFillColor () const { return Color (iw_circle_get_fill_color (IW_CIRCLE (self))); }

/*****************************************************************************/

void Circle::setStrokeColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_circle_set_stroke_color (IW_CIRCLE (self), &color);
}

/*****************************************************************************/

void Circle::setFillColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_circle_set_fill_color (IW_CIRCLE (self), &color);
}
