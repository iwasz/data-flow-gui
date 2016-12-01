/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_line.h"
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
G_DEFINE_TYPE (IwLine, iw_line, CLUTTER_TYPE_ACTOR);

/* macro for accessing the object's private structure */
#define IW_LINE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_LINE, IwLinePrivate))

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
struct _IwLinePrivate {
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
static void iw_line_finalize (GObject *gobject)
{
        //        IwLinePrivate *priv = IW_LINE (gobject)->priv;

        //        clutter_color_free (priv->color);

        /* call the parent class' finalize() method */
        G_OBJECT_CLASS (iw_line_parent_class)->finalize (gobject);
}

static void iw_line_pick (ClutterActor *actor, const ClutterColor *pick_color)
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

        float m = IW_LINE (actor)->priv->strokeWidth / 2.0 + 0.5;
        cogl_path_move_to (0 + m, 0 - m);
        cogl_path_line_to (width + m, height - m);
        cogl_path_line_to (width - m, height + m);
        cogl_path_line_to (0 - m, 0 + m);
        cogl_path_line_to (0 + m, 0 - m);
        cogl_path_fill ();
}

/* GObject class and instance initialization functions; note that
 * these have been placed after the Clutter implementation, as
 * they refer to the static function implementations above
 */

/* class init: attach functions to superclasses, define properties
 * and signals
 */
static void iw_line_class_init (IwLineClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
        GParamSpec *pspec;

        gobject_class->finalize = iw_line_finalize;
        //        gobject_class->set_property = iw_line_set_property;
        //        gobject_class->get_property = iw_line_get_property;

        // It still got destroyed even when I do not override the destroy method (like virtual function in C++).
        //        actor_class->allocate = iw_line_allocate;
        //        actor_class->paint = cb_button_paint;
        //        actor_class->paint_node = iw_line_paint_node;
        actor_class->pick = iw_line_pick;

        g_type_class_add_private (klass, sizeof (IwLinePrivate));
}

/* object init: create a private structure and pack
 * composed ClutterActors into it
 */
static void iw_line_init (IwLine *self)
{
        IwLinePrivate *priv;
        ClutterLayoutManager *layout;

        priv = self->priv = IW_LINE_GET_PRIVATE (self);

        //        clutter_actor_set_reactive (CLUTTER_ACTOR (self), TRUE);

        /* the only child of this actor is a ClutterBox with a
         * ClutterBinLayout: painting and allocation of the actor basically
         * involves painting and allocating this child box
         */
        //        layout = clutter_bin_layout_new (CLUTTER_BIN_ALIGNMENT_CENTER, CLUTTER_BIN_ALIGNMENT_CENTER);

        //        priv->child = clutter_actor_new ();
        //        clutter_actor_set_layout_manager (priv->child, layout);

        //        /* set the parent of the ClutterBox to this instance */
        //        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->child);

        //        /* add text label to the button; see the ClutterText API docs
        //         * for more information about available properties
        //         */
        //        priv->label = g_object_new (CLUTTER_TYPE_TEXT, "line-alignment", PANGO_ALIGN_CENTER, "ellipsize", PANGO_ELLIPSIZE_END, NULL);

        //        clutter_actor_add_child (priv->child, priv->label);

        //        /* add a ClutterClickAction on this actor, so we can proxy its
        //         * "clicked" signal into a signal from this actor
        //         */
        //        priv->click_action = clutter_click_action_new ();
        //        clutter_actor_add_action (CLUTTER_ACTOR (self), priv->click_action);

        //        g_signal_connect (priv->click_action, "clicked", G_CALLBACK (iw_line_clicked), NULL);
        priv->strokeColor = *clutter_color_get_static (CLUTTER_COLOR_BLACK);
        priv->strokeDash = 0;
        priv->strokeWidth = 3;

        priv->canvas = clutter_canvas_new ();
        //        clutter_canvas_set_size (CLUTTER_CANVAS (priv->canvas), 300, 300);
        clutter_actor_set_content (CLUTTER_ACTOR (self), priv->canvas);
        clutter_actor_set_content_scaling_filters (CLUTTER_ACTOR (self), CLUTTER_SCALING_FILTER_TRILINEAR, CLUTTER_SCALING_FILTER_LINEAR);
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

void iw_line_set_stroke_color (IwLine *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_LINE (self));
        self->priv->strokeColor = *color;
        clutter_content_invalidate (self->priv->canvas);
}

ClutterColor *iw_line_get_stroke_color (IwLine *self)
{
        g_return_val_if_fail (IW_IS_LINE (self), NULL);
        return &self->priv->strokeColor;
}

void iw_line_set_stroke_width (IwLine *self, gfloat w)
{
        g_return_if_fail (IW_IS_LINE (self));
        self->priv->strokeWidth = w;
        clutter_content_invalidate (self->priv->canvas);
}

gfloat iw_line_get_stroke_width (IwLine *self)
{
        g_return_val_if_fail (IW_IS_LINE (self), -1);
        return self->priv->strokeWidth;
}

void iw_line_set_stroke_dash (IwLine *self, gfloat w)
{
        g_return_if_fail (IW_IS_LINE (self));
        self->priv->strokeDash = w;
        clutter_content_invalidate (self->priv->canvas);
}

gfloat iw_line_get_stroke_dash (IwLine *self)
{
        g_return_val_if_fail (IW_IS_LINE (self), -1);
        return self->priv->strokeDash;
}

static void iw_line_resize_accordingly (IwLine *self)
{
        float px = fmin (self->priv->ax, self->priv->bx);
        float py = fmin (self->priv->ay, self->priv->by);
        clutter_actor_set_position (CLUTTER_ACTOR (self), px, py);

        float qx = fmax (self->priv->ax, self->priv->bx);
        float qy = fmax (self->priv->ay, self->priv->by);
        clutter_actor_set_size (CLUTTER_ACTOR (self), qx - px, qy - py);
}

void iw_line_set_point_a (IwLine *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_LINE (self));
        self->priv->ax = x;
        self->priv->ay = y;
        iw_line_resize_accordingly (self);
}

void iw_line_get_point_a (IwLine *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_LINE (self));
        *x = self->priv->ax;
        *y = self->priv->ay;
}

void iw_line_set_point_b (IwLine *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_LINE (self));
        self->priv->bx = x;
        self->priv->by = y;
        iw_line_resize_accordingly (self);
}

void iw_line_get_point_b (IwLine *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_LINE (self));
        *x = self->priv->bx;
        *y = self->priv->by;
}

/**
 * iw_line_new:
 *
 * Creates a new #IwLine instance
 *
 * Returns: a new #IwLine
 */
ClutterActor *iw_line_new (void) { return g_object_new (IW_TYPE_LINE, NULL); }

static gboolean draw_line (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
{
        IwLinePrivate *priv = (IwLinePrivate *)data;

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

        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_width (cr, priv->strokeWidth);

        if (priv->strokeDash > 0) {
                double dashed1 = priv->strokeDash;
                cairo_set_dash (cr, &dashed1, 1, 0);
        }

        clutter_cairo_set_source_color (cr, &priv->strokeColor);

        // Prevent clipping.
        float margin = priv->strokeWidth / 2.0 + 0.5;

        float ax = priv->ax;
        float ay = priv->ay;
        float bx = priv->bx;
        float by = priv->by;

        if (ax < bx && ay < by) {
                cairo_move_to (cr, margin, margin);
                cairo_line_to (cr, width - margin, height - margin);
        }
        else if (ax > bx && ay > by) {
                cairo_move_to (cr, width - margin, height - margin);
                cairo_line_to (cr, margin, margin);
        }

        else if (ax > bx && ay < by) {
                cairo_move_to (cr, width - margin, margin);
                cairo_line_to (cr, margin, height - margin);
        }
        else if (ax < bx && ay > by) {
                cairo_move_to (cr, margin, height - margin);
                cairo_line_to (cr, width - margin, margin);
        }

        cairo_stroke (cr);
        return TRUE;
}

static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data)
{
        clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)), ceilf (clutter_actor_box_get_width (allocation)),
                                 ceilf (clutter_actor_box_get_height (allocation)));
}
