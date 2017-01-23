/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScaleLayer.h"

ScaleLayer::ScaleLayer ()
{
        self = clutter_actor_new ();
        clutter_actor_show (self);
        clutter_actor_set_reactive (self, true);
        clutter_actor_set_size (self, SCALE_SURFACE_WIDTH, SCALE_SURFACE_HEIGHT);

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

        //        float w, h;
        //        clutter_actor_get_size (self, &w, &h);
        // std::cerr << w << ", " << h << std::endl;

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
        double x, y;
        clutter_actor_get_scale (self, &x, &y);
        clutter_actor_set_scale (self, x / 1.1, x / 1.1);
}

/*****************************************************************************/

void ScaleLayer::zoom (double f) { clutter_actor_set_scale (self, f, f); }
