/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Stage.h"
#include <core/Exception.h>

Stage::Stage ()
{
        clutterWidget = gtk_clutter_embed_new ();
        self = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutterWidget));
        gtk_widget_set_can_focus (clutterWidget, TRUE);
        gtk_widget_set_focus_on_click (clutterWidget, TRUE);
        setCppImplementation ();
}

/*****************************************************************************/

Color Stage::getFillColor () const
{
        ClutterColor color;
        clutter_actor_get_background_color (self, &color);
        return Color (&color);
}

/*****************************************************************************/

void Stage::setFillColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        clutter_actor_set_background_color (self, &color);
}
