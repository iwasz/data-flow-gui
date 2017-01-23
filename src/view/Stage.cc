/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Stage.h"
#include <clutter/clutter.h>
#include <core/Exception.h>

#include <iostream>

/*****************************************************************************/

void on_stage_resize (ClutterActor *actor, ClutterActorBox *box, ClutterAllocationFlags flags, gpointer user_data);

/*****************************************************************************/

Stage::Stage ()
{
        clutterWidget = gtk_clutter_embed_new ();
        self = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutterWidget));
        gtk_widget_set_can_focus (clutterWidget, TRUE);
        gtk_widget_set_focus_on_click (clutterWidget, TRUE);
        clutter_stage_set_minimum_size (CLUTTER_STAGE (self), 100, 100);

        scale = clutter_actor_new ();
        clutter_actor_add_child (self, scale);
        clutter_actor_show (scale);
        clutter_actor_set_reactive (scale, true);
        clutter_actor_set_size (scale, SCALE_SURFACE_WIDTH, SCALE_SURFACE_HEIGHT);

//        float fx, fy;
//        clutter_actor_get_size (scale, &fx, &fy);
//        std::cerr << fx << ", " << fy << std::endl;

#if 1
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (scale, &c);
#endif

        //        clutter_actor_set_position (scale, -(SCALE_SURFACE_WIDTH + dim.width) / 2.0, -(SCALE_SURFACE_HEIGHT + dim.height) / 2.0);
        clutter_actor_set_pivot_point (scale, 0.5, 0.5);

        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_stage_resize), scale);
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

void Stage::zoomIn ()
{

        float w, h;
        clutter_actor_get_size (self, &w, &h);
        std::cerr << w << ", " << h << std::endl;

        double x, y;
        clutter_actor_get_scale (scale, &x, &y);
        double newScale = x * 1.1;

        if (newScale > 1) {
                newScale = 1;
        }

        clutter_actor_set_scale (scale, newScale, newScale);
}

/*****************************************************************************/

void Stage::zoomOut ()
{
        double x, y;
        clutter_actor_get_scale (scale, &x, &y);
        clutter_actor_set_scale (scale, x / 1.1, x / 1.1);
}

/*****************************************************************************/

void Stage::zoom (double f) { clutter_actor_set_scale (scale, f, f); }

/*****************************************************************************/

void on_stage_resize (ClutterActor *actor, ClutterActorBox *box, ClutterAllocationFlags flags, gpointer user_data)
{
        ClutterActor *scale = static_cast<ClutterActor *> (user_data);
        Box bb (Point (box->x1, box->y1), Point (box->x2, box->y2));
        Dimension dim = bb.getDimension ();
        // clutter_actor_set_size (scale, dim.width, dim.height);
        clutter_actor_set_position (scale, -(SCALE_SURFACE_WIDTH - dim.width) / 2.0, -(SCALE_SURFACE_HEIGHT - dim.height) / 2.0);
}
