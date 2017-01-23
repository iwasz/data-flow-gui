/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_circle.h"
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
G_DEFINE_TYPE (IwCircle, iw_circle, CLUTTER_TYPE_ACTOR);

/* macro for accessing the object's private structure */
#define IW_CIRCLE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_CIRCLE, IwCirclePrivate))

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
struct _IwCirclePrivate {
        ClutterColor fillColor;
        ClutterColor strokeColor;
        gboolean fill;
        gfloat strokeWidth;
        gfloat strokeDash;
        ClutterContent *canvas;
};

static gboolean draw_circle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data);
static gboolean idle_resize (gpointer data);
static void iw_circle_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags);

/* from http://mail.gnome.org/archives/gtk-devel-list/2004-July/msg00158.html:
 *
 * "The finalize method finishes releasing the remaining
 * resources just before the object itself will be freed from memory, and
 * therefore it will only be called once. The two step process helps break
 * cyclic references. Both dispose and finalize must chain up to their
 * parent objects by calling their parent's respective methods *after* they
 * have disposed or finalized their own members."
 */
static void iw_circle_finalize (GObject *gobject)
{
        //        IwCirclePrivate *priv = IW_CIRCLE (gobject)->priv;

        //        clutter_color_free (priv->color);

        /* call the parent class' finalize() method */
        G_OBJECT_CLASS (iw_circle_parent_class)->finalize (gobject);
}

static void iw_circle_pick (ClutterActor *actor, const ClutterColor *pick_color)
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

/* GObject class and instance initialization functions; note that
 * these have been placed after the Clutter implementation, as
 * they refer to the static function implementations above
 */

/* class init: attach functions to superclasses, define properties
 * and signals
 */
static void iw_circle_class_init (IwCircleClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
        GParamSpec *pspec;

        gobject_class->finalize = iw_circle_finalize;
        //        gobject_class->set_property = iw_circle_set_property;
        //        gobject_class->get_property = iw_circle_get_property;

        // It still got destroyed even when I do not override the destroy method (like virtual function in C++).
        actor_class->allocate = iw_circle_allocate;
        //        actor_class->paint = iw_circle_paint;
        //        actor_class->paint_node = iw_circle_paint_node;

        actor_class->pick = iw_circle_pick;

        g_type_class_add_private (klass, sizeof (IwCirclePrivate));
}

/* object init: create a private structure and pack
 * composed ClutterActors into it
 */
static void iw_circle_init (IwCircle *self)
{
        IwCirclePrivate *priv;
        ClutterLayoutManager *layout;

        priv = self->priv = IW_CIRCLE_GET_PRIVATE (self);

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
        //        clutter_canvas_set_size (CLUTTER_CANVAS (priv->canvas), 300, 300);
        clutter_actor_set_content (CLUTTER_ACTOR (self), priv->canvas);
        clutter_actor_set_content_scaling_filters (CLUTTER_ACTOR (self), CLUTTER_SCALING_FILTER_TRILINEAR, CLUTTER_SCALING_FILTER_LINEAR);
        g_object_unref (priv->canvas);

        /* connect our drawing code */
        g_signal_connect (priv->canvas, "draw", G_CALLBACK (draw_circle), priv);
        /* invalidate the canvas, so that we can draw before the main loop starts */
        clutter_content_invalidate (priv->canvas);

        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_actor_resize), NULL);
}

/* public API */
/* examples of public API functions which wrap functions
 * on internal actors
 */

/**
 * iw_circle_set_background_color:
 * @self: a #IwCircle
 * @color: the #ClutterColor to use for the button's background
 *
 * Set the color of the button's background
 */
void iw_circle_set_fill_color (IwCircle *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_CIRCLE (self));
        self->priv->fillColor = *color;
        clutter_content_invalidate (self->priv->canvas);
}

ClutterColor *iw_circle_get_fill_color (IwCircle *self)
{
        g_return_val_if_fail (IW_IS_CIRCLE (self), NULL);
        return &self->priv->fillColor;
}

void iw_circle_set_stroke_color (IwCircle *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_CIRCLE (self));
        self->priv->strokeColor = *color;
        clutter_content_invalidate (self->priv->canvas);
}

ClutterColor *iw_circle_get_stroke_color (IwCircle *self)
{
        g_return_val_if_fail (IW_IS_CIRCLE (self), NULL);
        return &self->priv->strokeColor;
}

void iw_circle_set_stroke_width (IwCircle *self, gfloat w)
{
        g_return_if_fail (IW_IS_CIRCLE (self));
        self->priv->strokeWidth = w;
        clutter_content_invalidate (self->priv->canvas);
}

gfloat iw_circle_get_stroke_width (IwCircle *self)
{
        g_return_val_if_fail (IW_IS_CIRCLE (self), -1);
        return self->priv->strokeWidth;
}

void iw_circle_set_stroke_dash (IwCircle *self, gfloat w)
{
        g_return_if_fail (IW_IS_CIRCLE (self));
        self->priv->strokeDash = w;
        clutter_content_invalidate (self->priv->canvas);
}

gfloat iw_circle_get_stroke_dash (IwCircle *self)
{
        g_return_val_if_fail (IW_IS_CIRCLE (self), -1);
        return self->priv->strokeDash;
}

void iw_circle_set_fill (IwCircle *self, gboolean b)
{
        g_return_if_fail (IW_IS_CIRCLE (self));
        self->priv->fill = b;
        clutter_content_invalidate (self->priv->canvas);
}

/*****************************************************************************/

gboolean iw_circle_is_fill (IwCircle *self)
{
        g_return_val_if_fail (IW_IS_CIRCLE (self), FALSE);
        return self->priv->fill;
}

/*****************************************************************************/

static void iw_circle_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags)
{
        float ax, ay;
        clutter_actor_get_position (actor, &ax, &ay);

        float tx, ty;
        clutter_actor_get_transformed_position (actor, &tx, &ty);

        ClutterVertex in, out = { 0, 0 };
        in.x = ax;
        in.y = ay;

        // clutter_actor_apply_relative_transform_to_point (actor, clutter_actor_get_parent (CLUTTER_ACTOR (self)), &in, &out);
        clutter_actor_apply_relative_transform_to_point (actor, NULL, &in, &out);
        // clutter_actor_apply_transform_to_point (CLUTTER_ACTOR (self), &in, &out);

        // TODO!!!! to się wywołuje dla każdego koła na scenie (nawet tych, których nie ruszam).
        // printf ("position : %f, %f, transformedPosition :  %f, %f, relative %f, %f, %p\n", ax, ay, tx, ty, out.x, out.y, actor);

        /*---------------------------------------------------------------------------*/

        ClutterActorBox newBox = *box;
        float dia = fmin (clutter_actor_box_get_width (box), clutter_actor_box_get_height (box));
        newBox.x2 = newBox.x1 + dia;
        newBox.y2 = newBox.y1 + dia;
        ClutterAllocationFlags newFlags = flags | CLUTTER_DELEGATE_LAYOUT;
        clutter_actor_set_allocation (actor, &newBox, newFlags);
}

/*****************************************************************************/

ClutterActor *iw_circle_new (void) { return g_object_new (IW_TYPE_CIRCLE, NULL); }

/*****************************************************************************/

static gboolean draw_circle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
{
        IwCirclePrivate *priv = (IwCirclePrivate *)data;

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

        gfloat radius = fmin (width, height) / 2.0;
        cairo_translate (cr, radius, radius);
        cairo_arc (cr, 0, 0, radius - priv->strokeWidth / 2.0 - 1, 0, G_PI * 2);

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

static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data)
{
        clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)), ceilf (clutter_actor_box_get_width (allocation)),
                                 ceilf (clutter_actor_box_get_height (allocation)));
}
