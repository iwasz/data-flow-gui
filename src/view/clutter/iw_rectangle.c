/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_rectangle.h"
#include <math.h>

G_DEFINE_TYPE (IwRectangle, iw_rectangle, IW_TYPE_ACTOR);

#define IW_RECTANGLE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_RECTANGLE, IwRectanglePrivate))

/*****************************************************************************/

struct _IwRectanglePrivate {
        int dummy;
};

static gboolean draw_rectangle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);

/*****************************************************************************/

static void iw_rectangle_class_init (IwRectangleClass *klass) { g_type_class_add_private (klass, sizeof (IwRectanglePrivate)); }

/*****************************************************************************/

static void iw_rectangle_init (IwRectangle *self)
{
#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self), &c);
#endif

        ClutterContent *canvas = iw_actor_get_canvas (IW_ACTOR (self));
        g_signal_connect (canvas, "draw", G_CALLBACK (draw_rectangle), self);
        clutter_content_invalidate (canvas);
}

/*****************************************************************************/

ClutterActor *iw_rectangle_new (void) { return g_object_new (IW_TYPE_RECTANGLE, NULL); }

/*****************************************************************************/

static gboolean draw_rectangle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
{
        IwRectangle *self = (IwRectangle *)data;

        cairo_save (cr);

        /*
         * clear the contents of the canvas, to avoid painting
         * over the previous frame
         */
        cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
        cairo_paint (cr);
        cairo_restore (cr);
        cairo_set_operator (cr, CAIRO_OPERATOR_OVER);

        gfloat strokeWidth = iw_actor_get_stroke_width (IW_ACTOR (self));
        gfloat strokeDash = iw_actor_get_stroke_dash (IW_ACTOR (self));
        ClutterColor *strokeColor = iw_actor_get_stroke_color (IW_ACTOR (self));
        ClutterColor *fillColor = iw_actor_get_fill_color (IW_ACTOR (self));
        gboolean isFill = iw_actor_is_fill (IW_ACTOR (self));

        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_width (cr, strokeWidth);

        if (strokeDash > 0) {
                double dashed1 = strokeDash;
                cairo_set_dash (cr, &dashed1, 1, 0);
        }

        float mr = strokeWidth / 2.0 + 1;
        cairo_move_to (cr, mr, mr);
        cairo_line_to (cr, width - mr, mr);
        cairo_line_to (cr, width - mr, height - mr);
        cairo_line_to (cr, mr, height - mr);
        cairo_line_to (cr, mr, mr);

        if (strokeWidth > 0) {
                clutter_cairo_set_source_color (cr, strokeColor);
                cairo_stroke_preserve (cr);
        }

        if (isFill) {
                clutter_cairo_set_source_color (cr, fillColor);
                cairo_fill (cr);
        }

        // we're done drawing
        return TRUE;
}
