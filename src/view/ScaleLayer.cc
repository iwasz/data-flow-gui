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
        gfloat initialX;
        gfloat initialY;
        gfloat initialZ;

        Point initialFocal;
        Point prevCenter;
        bool prevCenterSet = false;
        float scale = 1;
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

        //        if (center == Point ()) {
        //                clutter_actor_set_pivot_point (self, 0.5, 0.5);
        //        }
        //        else {
        //                float x = int(center.x * 100 / SCALE_SURFACE_SIZE + 0.5) / 100.0;
        //                float y = int(center.y * 100 / SCALE_SURFACE_SIZE + 0.5) / 100.0;
        //                std::cerr << center << ", " << center.x / SCALE_SURFACE_SIZE << ", " << center.y / SCALE_SURFACE_SIZE << ", " << Point (x,
        //                y) <<
        //                std::endl;
        //                // clutter_actor_set_pivot_point (self, double(center.x) / SCALE_SURFACE_SIZE, double(center.y) / SCALE_SURFACE_SIZE);
        //                clutter_actor_set_pivot_point (self, x, y);
        //        }

        clutter_actor_set_scale (self, newScale, newScale);
}

/*****************************************************************************/

#if 0
void ScaleLayer::zoomOut (const Point &center)
{
        ClutterActor *stage = clutter_actor_get_parent (self);
        float stageW, stageH;
        clutter_actor_get_size (stage, &stageW, &stageH);

        float scaleLayerW, scaleLayerH;
        clutter_actor_get_transformed_size (self, &scaleLayerW, &scaleLayerH);

        float scaleLayerNW, scaleLayerNH;
        clutter_actor_get_size (self, &scaleLayerNW, &scaleLayerNH);

        float scaleLayerX, scaleLayerY;
        clutter_actor_get_transformed_position (self, &scaleLayerX, &scaleLayerY);

        float scaleLayerNX, scaleLayerNY;
        clutter_actor_get_position (self, &scaleLayerNX, &scaleLayerNY);

        float cx, cy;
        // clutter_actor_transform_stage_point (self, center.x, center.y, &cx, &cy);
        ClutterVertex vin = { center.x, center.y, 0 };
        ClutterVertex vout;
        clutter_actor_apply_transform_to_point (self, &vin, &vout);
        cx = vout.x;
        cy = vout.y;
        // clutter_actor_transform_stage_point (self, stageW, stageH, &cx, &cy);

        std::cerr << "StageDim = [" << stageW << ", " << stageH << "], scaleLayerTransDim = [" << scaleLayerW << ", " << scaleLayerH
                  << "], scaleLayerTransPos = [" << scaleLayerX << ", " << scaleLayerY << "], scaleLayerPos = [" << scaleLayerNX << ", " << scaleLayerNY
                  << "], center = " << center << ", transStagePointCenter = {" << cx << ", " << cy << "}" << std::endl;

        ClutterActorBox box;
        clutter_actor_get_allocation_box (self, &box);

        gfloat tx, ty, tz;
        clutter_actor_get_translation (self, &tx, &ty, &tz);

        Dimension dif = Point (cx, cy) - impl->prevCenter;
        impl->prevCenter = Point (cx, cy);

        //        std::cerr << box.x1 << ", " << box.y1 << ", " << box.x2 << ", " << box.y2 << "||||" << tx << ", " << ty << " *** " << dif << std::endl;

        float dim = std::max (stageW, stageH);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        double scaleX, scaleY;
        clutter_actor_get_scale (self, &scaleX, &scaleY);

        if (scaleX <= minScale) {
                return;
        }

        //        if (scaleX >= 1.0) {
        //                clutter_actor_get_translation (self, &impl->initialX, &impl->initialY, &impl->initialZ);
        //                //impl->initialFocal = center;
        //                impl->initialFocal = Point (cx, cy);

        if (center == Point ()) {
                clutter_actor_set_pivot_point (self, 0.5, 0.5);
        }
        else {
                std::cerr << center << ", " << double(center.x) / scaleLayerNW << ", " << double(center.y) / scaleLayerNH << std::endl;
                clutter_actor_set_pivot_point (self, double(center.x) / scaleLayerNW, double(center.y) / scaleLayerNH);
        }
        //        }

        clutter_actor_set_scale (self, scaleX / 1.1, scaleY / 1.1);

        //        gfloat x = impl->initialX + cx - impl->initialFocal.x;
        //        gfloat y = impl->initialY + cy - impl->initialFocal.y;

        //        if (impl->prevCenterSet) {
        //                gfloat z;
        //                clutter_actor_get_translation (self, NULL, NULL, &z);
        //                clutter_actor_set_translation (self, -dif.width, -dif.height, z);
        //        }

        impl->prevCenterSet = true;
        //        clutter_actor_set_scale_full (self, scaleX / 1.1, scaleX / 1.1, center.x, center.y);
}
#endif

#if 0
void ScaleLayer::zoomOut (const Point &center)
{
        ClutterActor *stage = clutter_actor_get_parent (self);

        float stageW, stageH;
        clutter_actor_get_size (stage, &stageW, &stageH);

        float scaleLayerNW, scaleLayerNH;
        clutter_actor_get_size (self, &scaleLayerNW, &scaleLayerNH);

        float dim = std::max (stageW, stageH);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        double scaleX, scaleY;
        clutter_actor_get_scale (self, &scaleX, &scaleY);

        if (scaleX <= minScale) {
                return;
        }

        if (center == Point ()) {
                clutter_actor_set_pivot_point (self, 0.5, 0.5);
        }
        else {
                std::cerr << center << ", " << double(center.x) / scaleLayerNW << ", " << double(center.y) / scaleLayerNH << std::endl;
                clutter_actor_set_pivot_point (self, double(center.x) / scaleLayerNW, double(center.y) / scaleLayerNH);
        }

        clutter_actor_set_scale (self, scaleX / 1.1, scaleY / 1.1);
}
#endif

#if 0
void ScaleLayer::zoomOut (const Point &center)
{
        ClutterActor *stage = clutter_actor_get_parent (self);

        float stageW, stageH;
        clutter_actor_get_size (stage, &stageW, &stageH);

        float scaleLayerNW, scaleLayerNH;
        clutter_actor_get_size (self, &scaleLayerNW, &scaleLayerNH);

        float dim = std::max (stageW, stageH);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        /*---------------------------------------------------------------------------*/

        ClutterMatrix transform;
        clutter_matrix_init_identity (&transform);
        //clutter_actor_get_transform (self, &transform);

        ClutterActorBox box;
        clutter_actor_get_allocation_box (self, &box);

        float pivot_x = (box.x2 - box.x1) * (double(center.x) / scaleLayerNW);
        float pivot_y = (box.y2 - box.y1) * (double(center.y) / scaleLayerNH);

        std::cerr << pivot_x << ", " << pivot_y << std::endl;

        gfloat tx, ty, tz;
        clutter_actor_get_translation (self, &tx, &ty, &tz);

        float px = pivot_x + tx;
        float py = pivot_y + ty;

        cogl_matrix_translate (&transform, px, py, 0);
        impl->scale /= 1.1;
        cogl_matrix_scale (&transform, impl->scale, impl->scale, 1);
        cogl_matrix_translate (&transform, -px, -py, 0);

        clutter_actor_set_transform (self, &transform);
}
#endif

/*****************************************************************************/

#if 0
void ScaleLayer::zoomOut (const Point &center)
{
        ClutterActor *stage = clutter_actor_get_parent (self);

        float stageW, stageH;
        clutter_actor_get_size (stage, &stageW, &stageH);

        float scaleLayerNW, scaleLayerNH;
        clutter_actor_get_size (self, &scaleLayerNW, &scaleLayerNH);

        float dim = std::max (stageW, stageH);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        /*---------------------------------------------------------------------------*/

        ClutterMatrix transform;
        clutter_matrix_init_identity (&transform);




        ClutterActorBox box;
        //clutter_actor_get_allocation_box (self, &box);


        float scaleLayerW, scaleLayerH;
        clutter_actor_get_transformed_size (self, &scaleLayerW, &scaleLayerH);

        float scaleLayerX, scaleLayerY;
        clutter_actor_get_transformed_position (self, &scaleLayerX, &scaleLayerY);

        float pivot_x = (scaleLayerW) * (double(center.x) / scaleLayerNW);
        float pivot_y = (scaleLayerH) * (double(center.y) / scaleLayerNH);

        std::cerr << pivot_x << ", " << pivot_y << std::endl;

        gfloat tx, ty, tz;
        clutter_actor_get_translation (self, &tx, &ty, &tz);

        float px = -scaleLayerX + pivot_x + tx;
        float py = -scaleLayerY + pivot_y + ty;

        cogl_matrix_translate (&transform, px, py, 0);
        impl->scale /= 1.1;
        cogl_matrix_scale (&transform, impl->scale, impl->scale, 1);
        cogl_matrix_translate (&transform, -px, -py, 0);

        clutter_actor_set_transform (self, &transform);
}
#endif

#if 1
void ScaleLayer::zoomOut (const Point &center)
{
        ClutterActor *stage = clutter_actor_get_parent (self);

        float stageW, stageH;
        clutter_actor_get_size (stage, &stageW, &stageH);

        float scaleLayerNW, scaleLayerNH;
        clutter_actor_get_size (self, &scaleLayerNW, &scaleLayerNH);

        float dim = std::max (stageW, stageH);
        double minScale = dim / SCALE_SURFACE_SIZE + 0.05;

        /*---------------------------------------------------------------------------*/

        ClutterMatrix transform;
        clutter_matrix_init_identity (&transform);
        //clutter_actor_get_transform (self, &transform);

        ClutterActorBox box;
        clutter_actor_get_allocation_box (self, &box);

        float cx1, cy1;
        clutter_actor_transform_stage_point (self, center.x, center.y, &cx1, &cy1);

        float pivot_x = (box.x2 - box.x1) * (double(cx1) / scaleLayerNW);
        float pivot_y = (box.y2 - box.y1) * (double(cy1) / scaleLayerNH);

        std::cerr << pivot_x << ", " << pivot_y << std::endl;

        gfloat tx, ty, tz;
        clutter_actor_get_translation (self, &tx, &ty, &tz);

        float px = pivot_x + tx;
        float py = pivot_y + ty;

        cogl_matrix_translate (&transform, px, py, 0);
        impl->scale /= 1.1;
        cogl_matrix_scale (&transform, impl->scale, impl->scale, 1);
        cogl_matrix_translate (&transform, -px, -py, 0);

        clutter_actor_set_transform (self, &transform);
}
#endif
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
        std::cerr << "Move by : " << m << std::endl;
}
