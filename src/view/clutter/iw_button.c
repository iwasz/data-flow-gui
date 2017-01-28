/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_button.h"

void buttonOnAllocate (void *ptr, float x1, float y1, float x2, float y2);
void buttonOnClick (void *ptr);
static gboolean draw_rectangle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);

/**
 * SECTION:cb-button
 * @short_description: Button widget
 *
 * A button widget with support for a text label and background color.
 */

/* convenience macro for GType implementations; see:
 * http://library.gnome.org/devel/gobject/2.27/gobject-Type-Information.html#G-DEFINE-TYPE:CAPS
 */
G_DEFINE_TYPE (CbButton, cb_button, IW_TYPE_ACTOR);

/* macro for accessing the object's private structure */
#define CB_BUTTON_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), CB_TYPE_BUTTON, CbButtonPrivate))

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
struct _CbButtonPrivate {
        //        ClutterActor *child;
        ClutterActor *label;
        ClutterAction *click_action;
        //        gchar *text;
        //        void *userData;
};

/* enumerates property identifiers for this class;
 * note that property identifiers should be non-zero integers,
 * so we add an unused PROP_0 to occupy the 0 position in the enum
 */
// enum { PROP_0, PROP_TEXT };

/* from http://mail.gnome.org/archives/gtk-devel-list/2004-July/msg00158.html:
 *
 * "The finalize method finishes releasing the remaining
 * resources just before the object itself will be freed from memory, and
 * therefore it will only be called once. The two step process helps break
 * cyclic references. Both dispose and finalize must chain up to their
 * parent objects by calling their parent's respective methods *after* they
 * have disposed or finalized their own members."
 */
// static void cb_button_finalize (GObject *gobject)
//{
//        CbButtonPrivate *priv = CB_BUTTON (gobject)->priv;

//        g_free (priv->text);

//        /* call the parent class' finalize() method */
//        G_OBJECT_CLASS (cb_button_parent_class)->finalize (gobject);
//}

/* enables objects to be uniformly treated as GObjects;
 * also exposes properties so they become scriptable, e.g.
 * through ClutterScript
 */
// static void cb_button_set_property (GObject *gobject, guint prop_id, const GValue *value, GParamSpec *pspec)
//{
//        CbButton *button = CB_BUTTON (gobject);

//        switch (prop_id) {
//        case PROP_TEXT:
//                cb_button_set_text (button, g_value_get_string (value));
//                break;

//        default:
//                G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
//                break;
//        }
//}

/* enables objects to be uniformly treated as GObjects */
// static void cb_button_get_property (GObject *gobject, guint prop_id, GValue *value, GParamSpec *pspec)
//{
//        CbButtonPrivate *priv = CB_BUTTON (gobject)->priv;

//        switch (prop_id) {
//        case PROP_TEXT:
//                g_value_set_string (value, priv->text);
//                break;

//        default:
//                G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
//                break;
//        }
//}

/* ClutterActor implementation
 *
 * we only implement destroy(), get_preferred_height(), get_preferred_width(),
 * allocate(), and paint(), as this is the minimum we can get away with
 */

/* composite actors should implement destroy(), and inside their
 * implementation destroy any actors they are composed from;
 * in this case, we just destroy the child ClutterBox
 */
// static void cb_button_destroy (ClutterActor *self)
//{
//        CbButtonPrivate *priv = CB_BUTTON (self)->priv;

//        /* we just destroy the child, and let the child
//         * deal with destroying _its_ children; note that we have a guard
//         * here in case the child has already been destroyed
//         */
//        if (priv->child) {
//                clutter_actor_destroy (priv->child);
//                priv->child = NULL;
//        }

//        /* chain up to destroy() on the parent ClutterActorClass;
//         * note that we check the parent class has a destroy() implementation
//         * before calling it
//         */
//        if (CLUTTER_ACTOR_CLASS (cb_button_parent_class)->destroy) CLUTTER_ACTOR_CLASS (cb_button_parent_class)->destroy (self);
//}

/* get_preferred_height and get_preferred_width defer to the
 * internal ClutterBox, adding 20px padding on each axis;
 * min_*_p is the minimum height or width the actor should occupy
 * to be useful; natural_*_p is the height or width the actor
 * would occupy if not constrained
 *
 * note that if we required explicit sizing for CbButtons
 * (i.e. a developer must set their height and width),
 * we wouldn't need to implement these functions
 */
static void cb_button_get_preferred_height (ClutterActor *self, gfloat for_width, gfloat *min_height_p, gfloat *natural_height_p)
{
        CbButtonPrivate *priv = CB_BUTTON (self)->priv;

        clutter_actor_get_preferred_height (self, for_width, min_height_p, natural_height_p);

        *min_height_p += 20.0;
        *natural_height_p += 20.0;
}

static void cb_button_get_preferred_width (ClutterActor *self, gfloat for_height, gfloat *min_width_p, gfloat *natural_width_p)
{
        CbButtonPrivate *priv = CB_BUTTON (self)->priv;

        clutter_actor_get_preferred_width (self, for_height, min_width_p, natural_width_p);

        *min_width_p += 20.0;
        *natural_width_p += 20.0;
}

/* use the actor's allocation for the ClutterBox */
static void cb_button_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags)
{
        CbButtonPrivate *priv = CB_BUTTON (actor)->priv;
        ClutterActorBox child_box = {
                0,
        };

        /* set the allocation for the whole button */
        CLUTTER_ACTOR_CLASS (cb_button_parent_class)->allocate (actor, box, flags);

        /* make the child (the ClutterBox) fill the parent;
         * note that this allocation box is relative to the
         * coordinates of the whole button actor, so we can't just
         * use the box passed into this function; instead, it
         * is adjusted to span the whole of the actor, from its
         * top-left corner (0,0) to its bottom-right corner
         * (width,height)
         */
        //        child_box.x1 = 0.0;
        //        child_box.y1 = 0.0;
        //        child_box.x2 = clutter_actor_box_get_width (box);
        //        child_box.y2 = clutter_actor_box_get_height (box);

        //        clutter_actor_set_allocation (actor, &child_box, flags);
        buttonOnAllocate (iw_actor_get_user_data (IW_ACTOR (actor)), child_box.x1, child_box.y1, child_box.x2, child_box.y2);
}

/* paint function implementation: just calls paint() on the ClutterBox */
// static void cb_button_paint (ClutterActor *actor)
//{
//        CbButtonPrivate *priv = CB_BUTTON (actor)->priv;
//        clutter_actor_paint (priv->child);
//}

/* proxy ClickAction signals so they become signals from the actor */
static void cb_button_clicked (ClutterClickAction *action, ClutterActor *actor, gpointer user_data)
{
        buttonOnClick (iw_actor_get_user_data (IW_ACTOR (actor)));
}

/* GObject class and instance initialization functions; note that
 * these have been placed after the Clutter implementation, as
 * they refer to the static function implementations above
 */

/* class init: attach functions to superclasses, define properties
 * and signals
 */
static void cb_button_class_init (CbButtonClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
        //        GParamSpec *pspec;

        //        gobject_class->finalize = cb_button_finalize;
        //        gobject_class->set_property = cb_button_set_property;
        //        gobject_class->get_property = cb_button_get_property;

        //        actor_class->destroy = cb_button_destroy;
        actor_class->get_preferred_height = cb_button_get_preferred_height;
        actor_class->get_preferred_width = cb_button_get_preferred_width;
        actor_class->allocate = cb_button_allocate;
        //        actor_class->paint = cb_button_paint;

        g_type_class_add_private (klass, sizeof (CbButtonPrivate));

        /**
         * CbButton:text:
         *
         * The text shown on the #CbButton
         */
        //        pspec = g_param_spec_string ("text", "Text", "Text of the button", NULL, G_PARAM_READWRITE);
        //        g_object_class_install_property (gobject_class, PROP_TEXT, pspec);
}

/* object init: create a private structure and pack
 * composed ClutterActors into it
 */
static void cb_button_init (CbButton *self)
{
        CbButtonPrivate *priv;
        ClutterLayoutManager *layout;

        priv = self->priv = CB_BUTTON_GET_PRIVATE (self);
        clutter_actor_set_reactive (CLUTTER_ACTOR (self), TRUE);

        //        layout = clutter_bin_layout_new (CLUTTER_BIN_ALIGNMENT_CENTER, CLUTTER_BIN_ALIGNMENT_CENTER);
        //        clutter_actor_set_layout_manager (CLUTTER_ACTOR (self), layout);

        priv->label = clutter_text_new ();
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->label);
        clutter_text_set_font_name (CLUTTER_TEXT (priv->label), "180px");
        clutter_text_set_text (CLUTTER_TEXT (priv->label), "Hello world");
        clutter_text_set_editable (CLUTTER_TEXT (priv->label), FALSE);
        clutter_text_set_selectable (CLUTTER_TEXT (priv->label), TRUE);
        clutter_text_set_single_line_mode (CLUTTER_TEXT (priv->label), TRUE);
        static ClutterColor c = { 0xff, 0x00, 0x00, 0xff };
        clutter_text_set_color (CLUTTER_TEXT (priv->label), &c);
        clutter_actor_set_reactive (priv->label, TRUE);

        /* add a ClutterClickAction on this actor, so we can proxy its
         * "clicked" signal into a signal from this actor
         */
        priv->click_action = clutter_click_action_new ();
        clutter_actor_add_action (CLUTTER_ACTOR (self), priv->click_action);
        g_signal_connect (priv->click_action, "clicked", G_CALLBACK (cb_button_clicked), NULL);

        ClutterContent *canvas = iw_actor_get_canvas (IW_ACTOR (self));
        g_signal_connect (canvas, "draw", G_CALLBACK (draw_rectangle), self);
        clutter_content_invalidate (canvas);
}

/**
 * cb_button_set_text_color:
 * @self: a #CbButton
 * @color: the #ClutterColor to use as the color for the button text
 *
 * Set the color of the text on the button
 */
void cb_button_set_text_color (CbButton *self, const ClutterColor *color)
{
        g_return_if_fail (CB_IS_BUTTON (self));
        clutter_text_set_color (CLUTTER_TEXT (self->priv->label), color);
}

/**
 * cb_button_set_text:
 * @self: a #CbButton
 * @text: the text to display on the button
 *
 * Set the text on the button
 */
void cb_button_set_text (CbButton *self, const gchar *text)
{
        g_return_if_fail (CB_IS_BUTTON (self));
        clutter_text_set_text (CLUTTER_TEXT (self->priv->label), text);
}

/**
 * cb_button_get_text:
 * @self: a #CbButton
 *
 * Get the text displayed on the button
 *
 * Returns: the button's text. This must not be freed by the application.
 */
const gchar *cb_button_get_text (CbButton *self)
{
        g_return_val_if_fail (CB_IS_BUTTON (self), NULL);
        return clutter_text_get_text (CLUTTER_TEXT (self->priv->label));
}

/**
 * cb_button_new:
 *
 * Creates a new #CbButton instance
 *
 * Returns: a new #CbButton
 */
ClutterActor *cb_button_new (void) { return g_object_new (CB_TYPE_BUTTON, NULL); }

/*****************************************************************************/

static gboolean draw_rectangle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
{
        CbButton *self = (CbButton *)data;

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

        return TRUE;
}
