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

void ScaleLayer::zoomIn (const primitives::Point &center)
{
        double x, y;
        clutter_actor_get_scale (self, &x, &y);

        if (x >= 1) {
                return;
        }

        double newScale = x * 1.1;

        if (newScale >= 1) {
                newScale = 1;
        }

        //        if (center == primitives::Point ()) {
        //                clutter_actor_set_pivot_point (self, 0.5, 0.5);
        //        }
        //        else {
        //                float x = int(center.x * 100 / SCALE_SURFACE_SIZE + 0.5) / 100.0;
        //                float y = int(center.y * 100 / SCALE_SURFACE_SIZE + 0.5) / 100.0;
        //                std::cerr << center << ", " << center.x / SCALE_SURFACE_SIZE << ", " << center.y / SCALE_SURFACE_SIZE << ", " << primitives::Point (x,
        //                y) <<
        //                std::endl;
        //                // clutter_actor_set_pivot_point (self, double(center.x) / SCALE_SURFACE_SIZE, double(center.y) / SCALE_SURFACE_SIZE);
        //                clutter_actor_set_pivot_point (self, x, y);
        //        }

        clutter_actor_set_scale (self, newScale, newScale);
}

/*****************************************************************************/

void ScaleLayer::zoomOut (const primitives::Point &center)
{
        ClutterActor *stage = clutter_actor_get_parent (self);
        float stageW, stageH;
        clutter_actor_get_size (stage, &stageW, &stageH);

        float scaleLayerW, scaleLayerH;
        clutter_actor_get_transformed_size (self, &scaleLayerW, &scaleLayerH);

        float scaleLayerX, scaleLayerY;
        clutter_actor_get_transformed_position (self, &scaleLayerX, &scaleLayerY);

        float cx, cy;
        // clutter_actor_transform_stage_point (self, center.x, center.y, &cx, &cy);
        clutter_actor_transform_stage_point (self, stageW, stageH, &cx, &cy);

        std::cerr << stageW << ", " << stageH << ", "
                  << ", " << scaleLayerW << ", " << scaleLayerH << ", " << scaleLayerX << ", " << scaleLayerY << center << ", {" << cx << ", " << cy << "}"
                  << std::endl;

        float dim = std::max (stageW, stageH);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        double scaleX, scaleY;
        clutter_actor_get_scale (self, &scaleX, &scaleY);

        if (scaleX <= minScale) {
                return;
        }

        //        if (center == primitives::Point ()) {
        //                clutter_actor_set_pivot_point (self, 0.5, 0.5);
        //        }
        //        else {
        //                std::cerr << center << ", " << double(center.x) / SCALE_SURFACE_SIZE << ", " << double(center.y) / SCALE_SURFACE_SIZE << std::endl;
        //                clutter_actor_set_pivot_point (self, double(center.x) / SCALE_SURFACE_SIZE, double(center.y) / SCALE_SURFACE_SIZE);
        //        }

        //        clutter_actor_set_scale (self, x / 1.1, x / 1.1);
        clutter_actor_set_scale_full (self, scaleX / 1.1, scaleX / 1.1, center.x, center.y);

        pan (primitives::Point ());
}

/*****************************************************************************/

void ScaleLayer::zoom (double f) { clutter_actor_set_scale (self, f, f); }

/*****************************************************************************/

void ScaleLayer::pan (primitives::Point const &n)
{

        float stageW, stageH, scaleW, scaleH, scaleX, scaleY;
        ClutterActor *stage = clutter_actor_get_parent (self);
        clutter_actor_get_size (stage, &stageW, &stageH);
        clutter_actor_get_transformed_size (self, &scaleW, &scaleH);
        clutter_actor_get_transformed_position (self, &scaleX, &scaleY);

        primitives::Point m = n;

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
