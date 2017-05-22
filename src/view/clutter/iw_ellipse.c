/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_ellipse.h"
#include <math.h>

G_DEFINE_TYPE (IwEllipse, iw_ellipse, IW_TYPE_ACTOR);

#define IW_ELLIPSE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_ELLIPSE, IwEllipsePrivate))

struct _IwEllipsePrivate {
        int dummy;
};

/*****************************************************************************/

// static gboolean draw_ellipse (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
// static void iw_ellipse_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags);

/*****************************************************************************/

static void iw_ellipse_paint (ClutterActor *actor)
{
        if (!clutter_actor_should_pick_paint (actor)) {
                return;
        }

        ClutterActorBox allocation = {
                0,
        };
        gfloat width, height;

        clutter_actor_get_allocation_box (actor, &allocation);
        clutter_actor_box_get_size (&allocation, &width, &height);

        cogl_path_new ();
        cogl_path_ellipse (width / 2.0, height / 2.0, width / 2.0, height / 2.0);

        gfloat strokeWidth = iw_actor_get_stroke_width (IW_ACTOR (actor));
        //        gfloat strokeDash = iw_actor_get_stroke_dash (IW_ACTOR (actor));
        ClutterColor *strokeColor = iw_actor_get_stroke_color (IW_ACTOR (actor));
        ClutterColor *fillColor = iw_actor_get_fill_color (IW_ACTOR (actor));
        gboolean isFill = iw_actor_is_fill (IW_ACTOR (actor));

        if (isFill) {
                cogl_set_source_color4ub (fillColor->red, fillColor->green, fillColor->blue, fillColor->alpha);
                cogl_path_fill_preserve ();
        }

        if (strokeWidth > 0) {
                cogl_set_source_color4ub (strokeColor->red, strokeColor->green, strokeColor->blue, strokeColor->alpha);
                cogl_path_stroke ();
        }

        for (ClutterActor *iter = clutter_actor_get_first_child (actor); iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
                clutter_actor_paint (iter);
        }
}

/*****************************************************************************/

static void iw_ellipse_pick (ClutterActor *actor, const ClutterColor *pick_color)
{
        if (!clutter_actor_should_pick_paint (actor)) {
                return;
        }

        ClutterActorBox allocation = {
                0,
        };
        gfloat width, height;

        clutter_actor_get_allocation_box (actor, &allocation);
        clutter_actor_box_get_size (&allocation, &width, &height);

        cogl_path_new ();
        cogl_set_source_color4ub (pick_color->red, pick_color->green, pick_color->blue, pick_color->alpha);
        cogl_path_ellipse (width / 2.0, height / 2.0, width / 2.0, height / 2.0);
        cogl_path_fill ();

        for (ClutterActor *iter = clutter_actor_get_first_child (actor); iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
                clutter_actor_paint (iter);
        }
}

/*****************************************************************************/

static void iw_ellipse_class_init (IwEllipseClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);

        actor_class->pick = iw_ellipse_pick;
        actor_class->paint = iw_ellipse_paint;

        g_type_class_add_private (klass, sizeof (IwEllipsePrivate));
}

/*****************************************************************************/

static void iw_ellipse_init (IwEllipse *self)
{
#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self), &c);
#endif

        //        iw_actor_create_canvas (IW_ACTOR (self));
        //        ClutterContent *canvas = iw_actor_get_canvas (IW_ACTOR (self));
        //        g_signal_connect (canvas, "draw", G_CALLBACK (draw_ellipse), self);
        //        clutter_content_invalidate (canvas);
}

/*****************************************************************************/

// static void iw_ellipse_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags)
//{
//#if 0
//        float ax, ay;
//        clutter_actor_get_position (actor, &ax, &ay);

//        float tx, ty;
//        clutter_actor_get_transformed_position (actor, &tx, &ty);

//        ClutterVertex in, out = { 0, 0 };
//        in.x = ax;
//        in.y = ay;

//        // clutter_actor_apply_relative_transform_to_point (actor, clutter_actor_get_parent (CLUTTER_ACTOR (self)), &in, &out);
//        clutter_actor_apply_relative_transform_to_point (actor, NULL, &in, &out);
//        // clutter_actor_apply_transform_to_point (CLUTTER_ACTOR (self), &in, &out);

//        // TODO!!!! to się wywołuje dla każdego koła na scenie (nawet tych, których nie ruszam).
//        // printf ("position : %f, %f, transformedPosition :  %f, %f, relative %f, %f, %p\n", ax, ay, tx, ty, out.x, out.y, actor);
//#endif
//        /*---------------------------------------------------------------------------*/

//        ClutterActorBox newBox = *box;
//        float dia = fmin (clutter_actor_box_get_width (box), clutter_actor_box_get_height (box));
//        newBox.x2 = newBox.x1 + dia;
//        newBox.y2 = newBox.y1 + dia;
//        ClutterAllocationFlags newFlags = flags | CLUTTER_DELEGATE_LAYOUT;
//        clutter_actor_set_allocation (actor, &newBox, newFlags);
//}

/*****************************************************************************/

ClutterActor *iw_ellipse_new (void) { return g_object_new (IW_TYPE_ELLIPSE, NULL); }

/*****************************************************************************/

// static gboolean draw_ellipse (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
//{
//        IwEllipse *self = (IwEllipse *)data;

//        cairo_save (cr);

//        /*
//         * clear the contents of the canvas, to avoid painting
//         * over the previous frame
//         */
//        cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
//        cairo_paint (cr);
//        cairo_restore (cr);
//        cairo_set_operator (cr, CAIRO_OPERATOR_OVER);

//        gfloat strokeWidth = iw_actor_get_stroke_width (IW_ACTOR (self));
//        gfloat strokeDash = iw_actor_get_stroke_dash (IW_ACTOR (self));
//        ClutterColor *strokeColor = iw_actor_get_stroke_color (IW_ACTOR (self));
//        ClutterColor *fillColor = iw_actor_get_fill_color (IW_ACTOR (self));
//        gboolean isFill = iw_actor_is_fill (IW_ACTOR (self));

//        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
//        cairo_set_line_width (cr, strokeWidth);

//        if (strokeDash > 0) {
//                double dashed1 = strokeDash;
//                cairo_set_dash (cr, &dashed1, 1, 0);
//        }

//        gfloat radius = fmin (width, height) / 2.0;
//        cairo_translate (cr, radius, radius);
//        cairo_arc (cr, 0, 0, radius - strokeWidth / 2.0 - 1, 0, G_PI * 2);

//        if (strokeWidth > 0) {
//                clutter_cairo_set_source_color (cr, strokeColor);
//                cairo_stroke_preserve (cr);
//        }

//        if (isFill) {
//                clutter_cairo_set_source_color (cr, fillColor);
//                cairo_fill (cr);
//        }

//        // we're done drawing
//        return TRUE;
//}
