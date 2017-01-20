/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Rectangle.h"
#include "clutter/iw_rectangle.h"
#include <core/Exception.h>

/*****************************************************************************/

Rectangle::Rectangle ()
{
        self = iw_rectangle_new ();
        clutter_actor_set_reactive (self, TRUE);
        setCppImplementation ();
}

/*****************************************************************************/

bool Rectangle::isFill () const { return iw_rectangle_is_fill (IW_RECTANGLE (self)); }

/*****************************************************************************/

void Rectangle::setFill (bool value) { iw_rectangle_set_fill (IW_RECTANGLE (self), value); }

/*****************************************************************************/

float Rectangle::getStrokeWidth () const { return iw_rectangle_get_stroke_width (IW_RECTANGLE (self)); }

/*****************************************************************************/

void Rectangle::setStrokeWidth (float value) { iw_rectangle_set_stroke_width (IW_RECTANGLE (self), value); }

/*****************************************************************************/

float Rectangle::getStrokeDash () const { return iw_rectangle_get_stroke_dash (IW_RECTANGLE (self)); }

/*****************************************************************************/

void Rectangle::setStrokeDash (float value) { iw_rectangle_set_stroke_dash (IW_RECTANGLE (self), value); }

/*****************************************************************************/

Color Rectangle::getStrokeColor () const { return Color (iw_rectangle_get_stroke_color (IW_RECTANGLE (self))); }

/*****************************************************************************/

Color Rectangle::getFillColor () const { return Color (iw_rectangle_get_fill_color (IW_RECTANGLE (self))); }

/*****************************************************************************/

void Rectangle::setStrokeColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_rectangle_set_stroke_color (IW_RECTANGLE (self), &color);
}

/*****************************************************************************/

void Rectangle::setFillColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_rectangle_set_fill_color (IW_RECTANGLE (self), &color);
}
