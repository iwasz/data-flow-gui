/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Stage.h"
#include "ScaleLayer.h"
#include <clutter/clutter.h>
#include <core/Exception.h>

/*****************************************************************************/

void on_stage_resize (ClutterActor *actor, ClutterActorBox *box, ClutterAllocationFlags flags, gpointer user_data);

/*****************************************************************************/

Stage::Stage () : scaleLayer (nullptr)
{
        clutterWidget = gtk_clutter_embed_new ();
        self = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutterWidget));
        gtk_widget_set_can_focus (clutterWidget, TRUE);
        gtk_widget_set_focus_on_click (clutterWidget, TRUE);
        clutter_stage_set_minimum_size (CLUTTER_STAGE (self), 100, 100);

        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_stage_resize), this);
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

/*****************************************************************************/

void on_stage_resize (ClutterActor *actor, ClutterActorBox *box, ClutterAllocationFlags flags, gpointer user_data)
{
        Stage *stage = static_cast<Stage *> (user_data);
        ClutterActor *scale = nullptr;

        if (stage->getScaleLayer ()) {
                scale = stage->getScaleLayer ()->getActor ();
        }
        else {
                return;
        }

        Box bb (Point (box->x1, box->y1), Point (box->x2, box->y2));
        Dimension dim = bb.getDimension ();
        // clutter_actor_set_size (scale, dim.width, dim.height);
        clutter_actor_set_position (scale, -(SCALE_SURFACE_WIDTH - dim.width) / 2.0, -(SCALE_SURFACE_HEIGHT - dim.height) / 2.0);
}

/*****************************************************************************/

void Stage::setScaleLayer (ScaleLayer *value)
{
        scaleLayer = value;
        value->setParent (this);
}
