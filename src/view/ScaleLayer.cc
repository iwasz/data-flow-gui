/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScaleLayer.h"
#include <iostream>

using namespace primitives;

ScaleLayer *ScaleLayer::instance;

/*****************************************************************************/

struct ScaleLayer::Impl {
};

/*****************************************************************************/

ScaleLayer::ScaleLayer () : impl (new Impl)
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

ScaleLayer::~ScaleLayer () { delete impl; }

/*****************************************************************************/

void ScaleLayer::zoomIn (const Point &center)
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

        scale (center, newScale);
}

/*****************************************************************************/

void ScaleLayer::zoomOut (const Point &center)
{
        ClutterActor *stage = clutter_actor_get_parent (self);

        float stageW, stageH;
        clutter_actor_get_size (stage, &stageW, &stageH);

        float dim = std::max (stageW, stageH);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        double scaleX, scaleY;
        clutter_actor_get_scale (self, &scaleX, &scaleY);

        if (scaleX <= minScale) {
                return;
        }

        scale (center, scaleX / 1.1);
}

/*****************************************************************************/

void ScaleLayer::scale (primitives::Point const &center, float newScale)
{
        float cx1, cy1;
        clutter_actor_transform_stage_point (self, center.x, center.y, &cx1, &cy1);

        if (center == Point ()) {
                clutter_actor_set_pivot_point (self, 0.5, 0.5);
        }
        else {
                float scaleLayerNW, scaleLayerNH;
                clutter_actor_get_size (self, &scaleLayerNW, &scaleLayerNH);
                clutter_actor_set_pivot_point (self, double(cx1) / scaleLayerNW, double(cy1) / scaleLayerNH);
        }

        clutter_actor_set_scale (self, newScale, newScale);

        // Idea taken from here : https://community.oracle.com/thread/1263955
        float cx2, cy2;
        clutter_actor_transform_stage_point (self, center.x, center.y, &cx2, &cy2);

        ClutterVertex vi1 = { 0, 0, 0 };
        ClutterVertex vo1;
        clutter_actor_apply_transform_to_point (self, &vi1, &vo1);

        ClutterVertex vi2 = { cx2 - cx1, cy2 - cy1, 0 };
        ClutterVertex vo2;
        clutter_actor_apply_transform_to_point (self, &vi2, &vo2);

        float mx = vo2.x - vo1.x;
        float my = vo2.y - vo1.y;

        clutter_actor_move_by (self, mx, my);
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
//        std::cerr << "Move by : " << m << std::endl;
}
