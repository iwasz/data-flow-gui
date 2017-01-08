/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Color.h"
#include <cassert>
#include <core/Exception.h>
#include <core/variant/Cast.h>
#include <core/variant/Variant.h>

/*****************************************************************************/

Color Color::fromString (std::string const &s)
{
        ClutterColor color;

        if (!clutter_color_from_string (&color, s.c_str ())) {
                throw Core::Exception ("Wrong color string [" + s + "].");
        }

        return fromClutterColor (&color);
}

/*****************************************************************************/

std::string Color::toString (Color const &c)
{
        ClutterColor cc = toClutterColor (c);
        gchar *buf = clutter_color_to_string (&cc);
        std::string ret = buf;
        g_free (buf);
        return ret;
}

/*****************************************************************************/

Color Color::fromClutterColor (ClutterColor *cc)
{
        Color c;
        c.r = cc->red;
        c.g = cc->green;
        c.b = cc->blue;
        c.a = cc->alpha;
        return c;
}

/*****************************************************************************/

ClutterColor Color::toClutterColor (Color const &c)
{
        ClutterColor cc;
        cc.red = c.r;
        cc.green = c.g;
        cc.blue = c.b;
        cc.alpha = c.a;
        return cc;
}

/*****************************************************************************/

bool ColorEditor::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        assert (output);

        try {
                *output = Core::Variant (Color::fromString (vcast<std::string> (input)));
        }
        catch (std::exception const &e) {
                dcError (context, std::string ("ColorEditor::convert. Exception : ") + e.what () + std::string (". Input variant : ") + input.toString ()
                                 + ", output variant : " + output->toString ());
                return false;
        }

        return true;
}
