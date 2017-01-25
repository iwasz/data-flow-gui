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

        setCppImplementation ();
}

/*****************************************************************************/

void ScaleLayer::zoomIn (const Point &center)
{
        double x, y;
        clutter_actor_get_scale (self, &x, &y);

        if (x >= 1) {
                return;
        }

        double newScale = x * 1.1;

        //        if (center == Point ()) {
        //                clutter_actor_set_pivot_point (self, 0.5, 0.5);
        //        }
        //        else {
        //                float x = int(center.x * 100 / SCALE_SURFACE_SIZE + 0.5) / 100.0;
        //                float y = int(center.y * 100 / SCALE_SURFACE_SIZE + 0.5) / 100.0;
        //                std::cerr << center << ", " << center.x / SCALE_SURFACE_SIZE << ", " << center.y / SCALE_SURFACE_SIZE << ", " << Point (x, y) <<
        //                std::endl;
        //                // clutter_actor_set_pivot_point (self, double(center.x) / SCALE_SURFACE_SIZE, double(center.y) / SCALE_SURFACE_SIZE);
        //                clutter_actor_set_pivot_point (self, x, y);
        //        }

        clutter_actor_set_scale (self, newScale, newScale);
}

/*****************************************************************************/

void ScaleLayer::zoomOut (const Point &center)
{
        ClutterActor *stage = clutter_actor_get_parent (self);
        float stageW, stageH;
        clutter_actor_get_size (stage, &stageW, &stageH);

        float dim = std::max (stageW, stageH);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        double x, y;
        clutter_actor_get_scale (self, &x, &y);

        if (x <= minScale) {
                return;
        }

        if (center == Point ()) {
                clutter_actor_set_pivot_point (self, 0.5, 0.5);
        }
        else {
                std::cerr << center << ", " << center.x / SCALE_SURFACE_SIZE << ", " << center.y / SCALE_SURFACE_SIZE << std::endl;
                clutter_actor_set_pivot_point (self, double(center.x) / SCALE_SURFACE_SIZE, double(center.y) / SCALE_SURFACE_SIZE);
        }

        clutter_actor_set_scale (self, x / 1.1, x / 1.1);

        pan (Point ());
}

/*****************************************************************************/

void ScaleLayer::zoom (double f) { clutter_actor_set_scale (self, f, f); }

/*****************************************************************************/

void ScaleLayer::pan (Point const &n)
{

        float stageW, stageH, scaleW, scaleH, scaleX, scaleY;
        ClutterActor *stage = clutter_actor_get_parent (self);
        clutter_actor_get_size (stage, &stageW, &stageH);
        clutter_actor_get_transformed_size (self, &scaleW, &scaleH);
        clutter_actor_get_transformed_position (self, &scaleX, &scaleY);

        Point m = n;

        if (scaleX + m.x > 0) {
                m.x = -scaleX;
        }

        if (scaleX + m.x < -(scaleW - stageW)) {
                m.x = -(scaleW - stageW) - scaleX;
        }

        if (scaleY + m.y > 0) {
                m.y = -scaleY;
        }

        if (scaleY + m.y < -(scaleH - stageH)) {
                m.y = -(scaleH - stageH) - scaleY;
        }

        clutter_actor_move_by (self, m.x, m.y);
}
