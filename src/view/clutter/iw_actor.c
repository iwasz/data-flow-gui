/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_actor.h"
#include <math.h>

void abstractActorOnFinalize (void *ptr);
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data);

/**
 * SECTION:cb-button
 * @short_description: Button widget
 *
 * A button widget with support for a text label and background color.
 */

/* convenience macro for GType implementations; see:
 * http://library.gnome.org/devel/gobject/2.27/gobject-Type-Information.html#G-DEFINE-TYPE:CAPS
 */
G_DEFINE_TYPE (IwActor, iw_actor, CLUTTER_TYPE_ACTOR);

/* macro for accessing the object's private structure */
#define IW_ACTOR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_ACTOR, IwActorPrivate))

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
struct _IwActorPrivate {
        ClutterColor fillColor;
        ClutterColor strokeColor;
        gboolean fill;
        gfloat strokeWidth;
        gfloat strokeDash;
        ClutterContent *canvas;
        void *userData;
};

/* from http://mail.gnome.org/archives/gtk-devel-list/2004-July/msg00158.html:
 *
 * "The finalize method finishes releasing the remaining
 * resources just before the object itself will be freed from memory, and
 * therefore it will only be called once. The two step process helps break
 * cyclic references. Both dispose and finalize must chain up to their
 * parent objects by calling their parent's respective methods *after* they
 * have disposed or finalized their own members."
 */
static void iw_actor_finalize (GObject *gobject)
{
        IwActorPrivate *priv = IW_ACTOR (gobject)->priv;
        if (priv->userData) {
                abstractActorOnFinalize (priv->userData);
        }
        /* call the parent class' finalize() method */
        G_OBJECT_CLASS (iw_actor_parent_class)->finalize (gobject);
}

/* GObject class and instance initialization functions; note that
 * these have been placed after the Clutter implementation, as
 * they refer to the static function implementations above
 */

/* class init: attach functions to superclasses, define properties
 * and signals
 */
static void iw_actor_class_init (IwActorClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
        GParamSpec *pspec;

        gobject_class->finalize = iw_actor_finalize;
        g_type_class_add_private (klass, sizeof (IwActorPrivate));
}

/* object init: create a private structure and pack
 * composed ClutterActors into it
 */
static void iw_actor_init (IwActor *self)
{
        IwActorPrivate *priv = self->priv = IW_ACTOR_GET_PRIVATE (self);

        priv->fillColor = *clutter_color_get_static (CLUTTER_COLOR_WHITE);
        priv->strokeColor = *clutter_color_get_static (CLUTTER_COLOR_BLACK);
        priv->fill = FALSE;
        priv->strokeDash = 0;
        priv->strokeWidth = 3;
        priv->userData = NULL;
#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self), &c);
#endif

        priv->canvas = clutter_canvas_new ();
        clutter_actor_set_content (CLUTTER_ACTOR (self), priv->canvas);
        clutter_actor_set_content_scaling_filters (CLUTTER_ACTOR (self), CLUTTER_SCALING_FILTER_TRILINEAR, CLUTTER_SCALING_FILTER_LINEAR);
        g_object_unref (priv->canvas);

        //        /* connect our drawing code */
        //        g_signal_connect (priv->canvas, "draw", G_CALLBACK (draw_actor), priv);
        //        /* invalidate the canvas, so that we can draw before the main loop starts */
        //        clutter_content_invalidate (priv->canvas);

        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_actor_resize), NULL);
}

ClutterContent *iw_actor_get_canvas (IwActor *self)
{
        g_return_val_if_fail (IW_IS_ACTOR (self), NULL);
        return self->priv->canvas;
}

void iw_actor_set_fill_color (IwActor *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_ACTOR (self));
        self->priv->fillColor = *color;
        clutter_content_invalidate (self->priv->canvas);
}

ClutterColor *iw_actor_get_fill_color (IwActor *self)
{
        g_return_val_if_fail (IW_IS_ACTOR (self), NULL);
        return &self->priv->fillColor;
}

void iw_actor_set_stroke_color (IwActor *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_ACTOR (self));
        self->priv->strokeColor = *color;
        clutter_content_invalidate (self->priv->canvas);
}

ClutterColor *iw_actor_get_stroke_color (IwActor *self)
{
        g_return_val_if_fail (IW_IS_ACTOR (self), NULL);
        return &self->priv->strokeColor;
}

void iw_actor_set_stroke_width (IwActor *self, gfloat w)
{
        g_return_if_fail (IW_IS_ACTOR (self));
        self->priv->strokeWidth = w;
        clutter_content_invalidate (self->priv->canvas);
}

gfloat iw_actor_get_stroke_width (IwActor *self)
{
        g_return_val_if_fail (IW_IS_ACTOR (self), -1);
        return self->priv->strokeWidth;
}

void iw_actor_set_stroke_dash (IwActor *self, gfloat w)
{
        g_return_if_fail (IW_IS_ACTOR (self));
        self->priv->strokeDash = w;
        clutter_content_invalidate (self->priv->canvas);
}

gfloat iw_actor_get_stroke_dash (IwActor *self)
{
        g_return_val_if_fail (IW_IS_ACTOR (self), -1);
        return self->priv->strokeDash;
}

void iw_actor_set_fill (IwActor *self, gboolean b)
{
        g_return_if_fail (IW_IS_ACTOR (self));
        self->priv->fill = b;
        clutter_content_invalidate (self->priv->canvas);
}

/*****************************************************************************/

gboolean iw_actor_is_fill (IwActor *self)
{
        g_return_val_if_fail (IW_IS_ACTOR (self), FALSE);
        return self->priv->fill;
}

void iw_actor_set_user_data (IwActor *self, void *p)
{
        g_return_if_fail (IW_IS_ACTOR (self));
        self->priv->userData = p;
}

void *iw_actor_get_user_data (IwActor *self)
{
        g_return_val_if_fail (IW_IS_ACTOR (self), NULL);
        return self->priv->userData;
}

/*****************************************************************************/

static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data)
{
        clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)), ceilf (clutter_actor_box_get_width (allocation)),
                                 ceilf (clutter_actor_box_get_height (allocation)));
}
