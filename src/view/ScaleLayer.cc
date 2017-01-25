/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScaleLayer.h"
#include <iostream>

ScaleLayer *ScaleLayer::instance;

/*****************************************************************************/

ScaleLayer::ScaleLayer ()
{
        self = clutter_actor_new ();
        clutter_actor_show (self);
        clutter_actor_set_reactive (self, true);
        clutter_actor_set_size (self, SCALE_SURFACE_SIZE, SCALE_SURFACE_SIZE);

#if 1
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (self, &c);
#endif

        clutter_actor_set_pivot_point (self, 0.5, 0.5);

        setCppImplementation ();
}

/*****************************************************************************/

void ScaleLayer::zoomIn ()
{
        double x, y;
        clutter_actor_get_scale (self, &x, &y);
        double newScale = x * 1.1;

        if (newScale > 1) {
                newScale = 1;
        }

        clutter_actor_set_scale (self, newScale, newScale);
}

/*****************************************************************************/

void ScaleLayer::zoomOut ()
{
        ClutterActor *stage = clutter_actor_get_parent (self);
        float w, h, w1, h1, x1, y1;
        clutter_actor_get_size (stage, &w, &h);
        clutter_actor_get_transformed_size (self, &w1, &h1);
        clutter_actor_get_transformed_position (self, &x1, &y1);

        float dim = std::max (w, h);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        double x, y;
        clutter_actor_get_scale (self, &x, &y);
        std::cerr << w << ", " << h << ", " << w1 << ", " << h1 << ", " << x1 << ", " << y1 << ", " << minScale << ", " << x << std::endl;

        if (x <= minScale) {
                return;
        }

        clutter_actor_set_scale (self, x / 1.1, x / 1.1);
}

/*****************************************************************************/

void ScaleLayer::zoom (double f) { clutter_actor_set_scale (self, f, f); }

/*****************************************************************************/

void ScaleLayer::pan (Point const &n)
{

        ClutterActor *stage = clutter_actor_get_parent (self);
        float w, h, w1, h1, x1, y1;
        clutter_actor_get_size (stage, &w, &h);
        clutter_actor_get_transformed_size (self, &w1, &h1);
        clutter_actor_get_transformed_position (self, &x1, &y1);

        Point m = n;

        if (x1 + m.x > 0) {
                m.x = -x1;
        }

        if (x1 + m.x < -(w1 - w)) {
                m.x = -(w1 - w) - x1;
        }

        if (y1 + m.y > 0) {
                m.y = -y1;
        }

        if (y1 + m.y < -(h1 - h)) {
                m.y = -(h1 - h) - y1;
        }

        clutter_actor_move_by (self, m.x, m.y);
}
