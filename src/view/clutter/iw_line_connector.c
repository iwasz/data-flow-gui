/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#if 0
#include "iw_line_connector.h"
#include <math.h>

/**
 * SECTION:cb-button
 * @short_description: Button widget
 *
 * A button widget with support for a text label and background color.
 */

/* convenience macro for GType implementations; see:
 * http://library.gnome.org/devel/gobject/2.27/gobject-Type-Information.html#G-DEFINE-TYPE:CAPS
 */
G_DEFINE_TYPE (IwLineConnector, iw_line_connector, CLUTTER_TYPE_ACTOR);

/* macro for accessing the object's private structure */
#define IW_LINE_CONNECTOR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_LINE_CONNECTOR, IwLineConnectorPrivate))

/* private structure - should only be accessed through the public API;
 * this is used to store member variables whose properties
 * need to be accessible from the implementation; for example, if we
 * intend to create wrapper functions which modify properties on the
 * actors composing an object, we should keep a reference to the actors
 * here
 *
 * this is also the place where other state variables go:
 * for example, you might record the current state of the button
 * (toggled on or off) or a background image
 */
struct _IwLineConnectorPrivate {
        ClutterColor strokeColor;
        gfloat strokeWidth;
        gfloat strokeDash;
        gfloat ax, ay;
        gfloat bx, by;
        ClutterContent *canvas;
};

static gboolean draw_line (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data);
static gboolean idle_resize (gpointer data);

/* from http://mail.gnome.org/archives/gtk-devel-list/2004-July/msg00158.html:
 *
 * "The finalize method finishes releasing the remaining
 * resources just before the object itself will be freed from memory, and
 * therefore it will only be called once. The two step process helps break
 * cyclic references. Both dispose and finalize must chain up to their
 * parent objects by calling their parent's respective methods *after* they
 * have disposed or finalized their own members."
 */
static void iw_line_connector_finalize (GObject *gobject)
{
        //        IwLineConnectorPrivate *priv = IW_LINE_CONNECTOR (gobject)->priv;

        //        clutter_color_free (priv->color);

        /* call the parent class' finalize() method */
        G_OBJECT_CLASS (iw_line_connector_parent_class)->finalize (gobject);
}

static void iw_line_connector_pick (ClutterActor *actor, const ClutterColor *pick_color)
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

        float m = IW_LINE_CONNECTOR (actor)->priv->strokeWidth / 2.0 + 0.5;
        cogl_path_move_to (0 + m, 0 - m);
        cogl_path_line_connector_to (width + m, height - m);
        cogl_path_line_connector_to (width - m, height + m);
        cogl_path_line_connector_to (0 - m, 0 + m);
        cogl_path_line_connector_to (0 + m, 0 - m);
        cogl_path_fill ();

        for (ClutterActor *iter = clutter_actor_get_first_child (actor); iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
                clutter_actor_paint (iter);
        }
}

/* GObject class and instance initialization functions; note that
 * these have been placed after the Clutter implementation, as
 * they refer to the static function implementations above
 */

/* class init: attach functions to superclasses, define properties
 * and signals
 */
static void iw_line_connector_class_init (IwLineConnectorClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
        GParamSpec *pspec;

        gobject_class->finalize = iw_line_connector_finalize;
        //        gobject_class->set_property = iw_line_connector_set_property;
        //        gobject_class->get_property = iw_line_connector_get_property;

        // It still got destroyed even when I do not override the destroy method (like virtual function in C++).
        //        actor_class->allocate = iw_line_connector_allocate;
        //        actor_class->paint = cb_button_paint;
        //        actor_class->paint_node = iw_line_connector_paint_node;
        actor_class->pick = iw_line_connector_pick;

        g_type_class_add_private (klass, sizeof (IwLineConnectorPrivate));
}

/* object init: create a private structure and pack
 * composed ClutterActors into it
 */
static void iw_line_connector_init (IwLineConnector *self)
{
        IwLineConnectorPrivate *priv;
        ClutterLayoutManager *layout;

        priv = self->priv = IW_LINE_CONNECTOR_GET_PRIVATE (self);

#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self), &c);
#endif

        priv->strokeColor = *clutter_color_get_static (CLUTTER_COLOR_BLACK);
        priv->strokeDash = 0;
        priv->strokeWidth = 3;

        priv->canvas = clutter_canvas_new ();
        //        clutter_canvas_set_size (CLUTTER_CANVAS (priv->canvas), 300, 300);
        clutter_actor_set_content (CLUTTER_ACTOR (self), priv->canvas);
        clutter_actor_set_content_scaling_filters (CLUTTER_ACTOR (self), CLUTTER_SCALING_FILTER_TRILINEAR, CLUTTER_SCALING_FILTER_LINE_CONNECTORAR);
        g_object_unref (priv->canvas);

        /* connect our drawing code */
        g_signal_connect (priv->canvas, "draw", G_CALLBACK (draw_line), priv);
        /* invalidate the canvas, so that we can draw before the main loop starts */
        clutter_content_invalidate (priv->canvas);

        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_actor_resize), NULL);
}

/* public API */
/* examples of public API functions which wrap functions
 * on internal actors
 */

void iw_line_connector_set_stroke_color (IwLineConnector *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_LINE_CONNECTOR (self));
        self->priv->strokeColor = *color;
        clutter_content_invalidate (self->priv->canvas);
}

ClutterColor *iw_line_connector_get_stroke_color (IwLineConnector *self)
{
        g_return_val_if_fail (IW_IS_LINE_CONNECTOR (self), NULL);
        return &self->priv->strokeColor;
}

void iw_line_connector_set_stroke_width (IwLineConnector *self, gfloat w)
{
        g_return_if_fail (IW_IS_LINE_CONNECTOR (self));
        self->priv->strokeWidth = w;
        clutter_content_invalidate (self->priv->canvas);
}

gfloat iw_line_connector_get_stroke_width (IwLineConnector *self)
{
        g_return_val_if_fail (IW_IS_LINE_CONNECTOR (self), -1);
        return self->priv->strokeWidth;
}

void iw_line_connector_set_stroke_dash (IwLineConnector *self, gfloat w)
{
        g_return_if_fail (IW_IS_LINE_CONNECTOR (self));
        self->priv->strokeDash = w;
        clutter_content_invalidate (self->priv->canvas);
}

gfloat iw_line_connector_get_stroke_dash (IwLineConnector *self)
{
        g_return_val_if_fail (IW_IS_LINE_CONNECTOR (self), -1);
        return self->priv->strokeDash;
}

static void iw_line_connector_resize_accordingly (IwLineConnector *self)
{
        float lw = self->priv->strokeWidth;
        float px = fmin (self->priv->ax, self->priv->bx);
        float py = fmin (self->priv->ay, self->priv->by);
        clutter_actor_set_position (CLUTTER_ACTOR (self), px - lw, py - lw);

        float qx = fmax (self->priv->ax, self->priv->bx);
        float qy = fmax (self->priv->ay, self->priv->by);
        clutter_actor_set_size (CLUTTER_ACTOR (self), qx - px + 2 * lw, qy - py + 2 * lw);
}

void iw_line_connector_set_point_a (IwLineConnector *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_LINE_CONNECTOR (self));
        self->priv->ax = x;
        self->priv->ay = y;
        iw_line_connector_resize_accordingly (self);
}

void iw_line_connector_get_point_a (IwLineConnector *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_LINE_CONNECTOR (self));
        *x = self->priv->ax;
        *y = self->priv->ay;
}

void iw_line_connector_set_point_b (IwLineConnector *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_LINE_CONNECTOR (self));
        self->priv->bx = x;
        self->priv->by = y;
        iw_line_connector_resize_accordingly (self);
}

void iw_line_connector_get_point_b (IwLineConnector *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_LINE_CONNECTOR (self));
        *x = self->priv->bx;
        *y = self->priv->by;
}

/**
 * iw_line_connector_new:
 *
 * Creates a new #IwLineConnector instance
 *
 * Returns: a new #IwLineConnector
 */
ClutterActor *iw_line_connector_new (void) { return g_object_new (IW_TYPE_LINE_CONNECTOR, NULL); }

static gboolean draw_line (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
{
        IwLineConnectorPrivate *priv = (IwLineConnectorPrivate *)data;

        cairo_save (cr);

        /* clear the contents of the canvas, to avoid painting
         * over the previous frame
         */
        cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
        cairo_paint (cr);

        cairo_restore (cr);

        cairo_set_operator (cr, CAIRO_OPERATOR_OVER);

        /* scale the modelview to the size of the surface */
        //        cairo_scale (cr, width, height);

        cairo_set_line_connector_cap (cr, CAIRO_LINE_CONNECTOR_CAP_ROUND);
        cairo_set_line_connector_width (cr, priv->strokeWidth);

        if (priv->strokeDash > 0) {
                double dashed1 = priv->strokeDash;
                cairo_set_dash (cr, &dashed1, 1, 0);
        }

        clutter_cairo_set_source_color (cr, &priv->strokeColor);

        // Prevent clipping.
        float margin = priv->strokeWidth /*/ 2.0 + 0.5*/;

        float ax = priv->ax;
        float ay = priv->ay;
        float bx = priv->bx;
        float by = priv->by;

        if (ax < bx && ay < by) {
                cairo_move_to (cr, margin, margin);
                cairo_line_connector_to (cr, width - margin, height - margin);
        }
        else if (ax > bx && ay > by) {
                cairo_move_to (cr, width - margin, height - margin);
                cairo_line_connector_to (cr, margin, margin);
        }

        else if (ax > bx && ay < by) {
                cairo_move_to (cr, width - margin, margin);
                cairo_line_connector_to (cr, margin, height - margin);
        }
        else if (ax < bx && ay > by) {
                cairo_move_to (cr, margin, height - margin);
                cairo_line_connector_to (cr, width - margin, margin);
        }

        cairo_stroke (cr);
        return TRUE;
}

static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data)
{
        clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)), ceilf (clutter_actor_box_get_width (allocation)),
                                 ceilf (clutter_actor_box_get_height (allocation)));
}
#endif
