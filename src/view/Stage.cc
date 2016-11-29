/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Stage.h"
#include <core/Exception.h>

void Stage::init ()
{
        clutterWidget = gtk_clutter_embed_new ();
        self = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutterWidget));
}

std::string Stage::getFillColor () const
{
        ClutterColor color;
        clutter_actor_get_background_color (self, &color);
        return std::string (clutter_color_to_string (&color));
}

void Stage::setFillColor (const std::string &color)
{
        ClutterColor stageColor;

        if (!clutter_color_from_string (&stageColor, color.c_str ())) {
                throw Core::Exception ("Wrong color string [" + color + "].");
        }

        clutter_actor_set_background_color (self, &stageColor);
}
