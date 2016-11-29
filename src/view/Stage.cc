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
        stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutterWidget));
        ClutterColor stageColor;

        if (!clutter_color_from_string (&stageColor, color.c_str ())) {
                throw Core::Exception ("Wrong color string [" + color + "].");
        }

        clutter_actor_set_background_color (CLUTTER_ACTOR (stage), &stageColor);
}
