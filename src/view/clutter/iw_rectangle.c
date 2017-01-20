/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_rectangle.h"
#include <math.h>

G_DEFINE_TYPE (IwRectangle, iw_rectangle, CLUTTER_TYPE_ACTOR);

#define IW_RECTANGLE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_RECTANGLE, IwRectanglePrivate))

/*****************************************************************************/

struct _IwRectanglePrivate {
        ClutterColor fillColor;
        ClutterColor strokeColor;
        gboolean fill;
        gfloat strokeWidth;
        gfloat strokeDash;
        ClutterContent *canvas;
};

static gboolean draw_rectangle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data);
static gboolean idle_resize (gpointer data);
static void iw_rectangle_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags);

/*****************************************************************************/

static void iw_rectangle_class_init (IwRectangleClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);

        // actor_class->allocate = iw_rectangle_allocate;
        // actor_class->pick = iw_rectangle_pick;

        g_type_class_add_private (klass, sizeof (IwRectanglePrivate));
}

/*****************************************************************************/

static void iw_rectangle_init (IwRectangle *self)
{
        IwRectanglePrivate *priv;
        ClutterLayoutManager *layout;

        priv = self->priv = IW_RECTANGLE_GET_PRIVATE (self);

        priv->fillColor = *clutter_color_get_static (CLUTTER_COLOR_WHITE);
        priv->strokeColor = *clutter_color_get_static (CLUTTER_COLOR_BLACK);
        priv->fill = FALSE;
        priv->strokeDash = 0;
        priv->strokeWidth = 3;

#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self), &c);
#endif

        priv->canvas = clutter_canvas_new ();
        clutter_actor_set_content (CLUTTER_ACTOR (self), priv->canvas);
        clutter_actor_set_content_scaling_filters (CLUTTER_ACTOR (self), CLUTTER_SCALING_FILTER_TRILINEAR, CLUTTER_SCALING_FILTER_LINEAR);
        g_object_unref (priv->canvas);

        /* connect our drawing code */
        g_signal_connect (priv->canvas, "draw", G_CALLBACK (draw_rectangle), priv);
        /* invalidate the canvas, so that we can draw before the main loop starts */
        clutter_content_invalidate (priv->canvas);

        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_actor_resize), NULL);
}

/*****************************************************************************/

void iw_rectangle_set_fill_color (IwRectangle *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_RECTANGLE (self));
        self->priv->fillColor = *color;
        clutter_content_invalidate (self->priv->canvas);
}

/*****************************************************************************/

ClutterColor *iw_rectangle_get_fill_color (IwRectangle *self)
{
        g_return_val_if_fail (IW_IS_RECTANGLE (self), NULL);
        return &self->priv->fillColor;
}

/*****************************************************************************/

void iw_rectangle_set_stroke_color (IwRectangle *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_RECTANGLE (self));
        self->priv->strokeColor = *color;
        clutter_content_invalidate (self->priv->canvas);
}

/*****************************************************************************/

ClutterColor *iw_rectangle_get_stroke_color (IwRectangle *self)
{
        g_return_val_if_fail (IW_IS_RECTANGLE (self), NULL);
        return &self->priv->strokeColor;
}

/*****************************************************************************/

void iw_rectangle_set_stroke_width (IwRectangle *self, gfloat w)
{
        g_return_if_fail (IW_IS_RECTANGLE (self));
        self->priv->strokeWidth = w;
        clutter_content_invalidate (self->priv->canvas);
}

/*****************************************************************************/

gfloat iw_rectangle_get_stroke_width (IwRectangle *self)
{
        g_return_val_if_fail (IW_IS_RECTANGLE (self), -1);
        return self->priv->strokeWidth;
}

/*****************************************************************************/

void iw_rectangle_set_stroke_dash (IwRectangle *self, gfloat w)
{
        g_return_if_fail (IW_IS_RECTANGLE (self));
        self->priv->strokeDash = w;
        clutter_content_invalidate (self->priv->canvas);
}

/*****************************************************************************/

gfloat iw_rectangle_get_stroke_dash (IwRectangle *self)
{
        g_return_val_if_fail (IW_IS_RECTANGLE (self), -1);
        return self->priv->strokeDash;
}

/*****************************************************************************/

void iw_rectangle_set_fill (IwRectangle *self, gboolean b)
{
        g_return_if_fail (IW_IS_RECTANGLE (self));
        self->priv->fill = b;
        clutter_content_invalidate (self->priv->canvas);
}

/*****************************************************************************/

gboolean iw_rectangle_is_fill (IwRectangle *self)
{
        g_return_val_if_fail (IW_IS_RECTANGLE (self), FALSE);
        return self->priv->fill;
}

/*****************************************************************************/

// static void iw_rectangle_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags)
//{
//        ClutterActorBox newBox = *box;
//        float dia = fmin (clutter_actor_box_get_width (box), clutter_actor_box_get_height (box));
//        newBox.x2 = newBox.x1 + dia;
//        newBox.y2 = newBox.y1 + dia;
//        ClutterAllocationFlags newFlags = flags | CLUTTER_DELEGATE_LAYOUT;
//        clutter_actor_set_allocation (actor, &newBox, newFlags);
//}

/*****************************************************************************/

ClutterActor *iw_rectangle_new (void) { return g_object_new (IW_TYPE_RECTANGLE, NULL); }

/*****************************************************************************/

static gboolean draw_rectangle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
{
        IwRectanglePrivate *priv = (IwRectanglePrivate *)data;

        cairo_save (cr);

        /*
         * clear the contents of the canvas, to avoid painting
         * over the previous frame
         */
        cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
        cairo_paint (cr);
        cairo_restore (cr);
        cairo_set_operator (cr, CAIRO_OPERATOR_OVER);

        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_width (cr, priv->strokeWidth);

        if (priv->strokeDash > 0) {
                double dashed1 = priv->strokeDash;
                cairo_set_dash (cr, &dashed1, 1, 0);
        }

        //        gfloat radius = fmin (width, height) / 2.0;
        //        cairo_translate (cr, radius, radius);
        //        cairo_arc (cr, 0, 0, radius - priv->strokeWidth / 2.0 - 1, 0, G_PI * 2);

        float mr = priv->strokeWidth / 2.0 + 1;
        cairo_move_to (cr, mr, mr);
        cairo_line_to (cr, width - mr, mr);
        cairo_line_to (cr, width - mr, height - mr);
        cairo_line_to (cr, mr, height - mr);
        cairo_line_to (cr, mr, mr);

        if (priv->strokeWidth > 0) {
                clutter_cairo_set_source_color (cr, &priv->strokeColor);
                cairo_stroke_preserve (cr);
        }

        if (priv->fill) {
                clutter_cairo_set_source_color (cr, &priv->fillColor);
                cairo_fill (cr);
        }

        // we're done drawing
        return TRUE;
}

/*****************************************************************************/

static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data)
{
        clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)), ceilf (clutter_actor_box_get_width (allocation)),
                                 ceilf (clutter_actor_box_get_height (allocation)));
}
