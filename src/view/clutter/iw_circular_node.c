/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_circular_node.h"
#include "iw_circle.h"
#include "view/clutter/iw_actor.h"
#include <math.h>

/* convenience macro for GType implementations; see:
 * http://library.gnome.org/devel/gobject/2.27/gobject-Type-Information.html#G-DEFINE-TYPE:CAPS
 */
G_DEFINE_TYPE (IwCircularNode, iw_circular_node, IW_TYPE_ABSTRACT_NODE);

/* macro for accessing the object's private structure */
#define IW_CIRCULAR_NODE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_CIRCULAR_NODE, IwCircularNodePrivate))

extern void circularNodeOnAllocate (void *circularNode, float x1, float y1, float x2, float y2);

/**
 * One input.
 */
struct _IwCircularNodePort {
        float x, y;
        ClutterActor *actor;
};

typedef struct _IwCircularNodePort IwCircularNodePort;

/*
 * Private structures.
 */
struct _IwCircularNodePrivate {
        ClutterLayoutManager *layout;
        ClutterActor *mainCircle;
        ClutterActor *label;
};

static gboolean do_draw (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data);
static void on_dimension_changed (GObject *gobject, GParamSpec *pspec, gpointer user_data);
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
static void iw_circular_node_finalize (GObject *gobject)
{
        //        IwCircularNodePrivate *priv = IW_CIRCULAR_NODE (gobject)->priv;
        //        clutter_color_free (priv->color);

        /* call the parent class' finalize() method */
        G_OBJECT_CLASS (iw_circular_node_parent_class)->finalize (gobject);
}

/*****************************************************************************/
#if 0
static void iw_circular_node_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags)
{
#if 0
        printf ("%f, %f, %f, %f\n", box->x1, box->y1, box->x2, box->y2);
#endif

        IwCircularNodePrivate *priv = IW_CIRCULAR_NODE (actor)->priv;

        /* set the allocation for the whole button */
        //  CLUTTER_ACTOR_CLASS (iw_circular_node_parent_class)->allocate (actor, box, flags);

        float boxW = clutter_actor_box_get_width (box);
        float boxH = clutter_actor_box_get_height (box);

#if 0
        ClutterActorBox labelBox;
        clutter_actor_get_allocation_box (priv->label, &labelBox);
        float labelW = clutter_actor_box_get_width (&labelBox);
        float labelH = clutter_actor_box_get_height (&labelBox);
        float maxW = fmax (boxW, labelW);
        float maxH = fmax (boxH, labelH);
        float dia = fmax (maxW, maxH);
        printf ("%f, %f, %f, %f, %f, %f, %f\n", boxW, boxH, labelW, labelH, maxW, maxH, dia);
#else
        float dia = fmin (boxW, boxH);
#endif

        ClutterActorBox newBox = *box;
        newBox.x2 = newBox.x1 + dia;
        newBox.y2 = newBox.y1 + dia;
        ClutterAllocationFlags newFlags = flags | CLUTTER_DELEGATE_LAYOUT;
        clutter_actor_set_allocation (actor, &newBox, newFlags);

        /* make the child (the ClutterBox) fill the parent;
         * note that this allocation box is relative to the
         * coordinates of the whole button actor, so we can't just
         * use the box passed into this function; instead, it
         * is adjusted to span the whole of the actor, from its
         * top-left corner (0,0) to its bottom-right corner
         * (width,height)
         */
        ClutterActorBox childBox;
        childBox.x1 = 0.0;
        childBox.y1 = 0.0;
        childBox.x2 = clutter_actor_box_get_width (&newBox);
        childBox.y2 = clutter_actor_box_get_height (&newBox);

        clutter_actor_allocate (priv->mainCircle, &childBox, flags);
        //        circularNodeOnAllocate (priv->userData, newBox.x1, newBox.y1, newBox.x2, newBox.y2);
}
#endif
/*****************************************************************************/

static void iw_circular_node_pick (ClutterActor *actor, const ClutterColor *pick_color)
{

        if (!clutter_actor_should_pick_paint (actor)) {
                return;
        }

        for (ClutterActor *iter = clutter_actor_get_first_child (actor); iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
                clutter_actor_paint (iter);
        }

        return;

#if 0
        IwCircularNodePrivate *priv = IW_CIRCULAR_NODE_GET_PRIVATE (actor);
        ClutterActorBox allocation = {
                0,
        };
        gfloat width, height;

        clutter_actor_get_allocation_box (priv->mainCircle, &allocation);
        clutter_actor_box_get_size (&allocation, &width, &height);

        cogl_path_new ();

        cogl_set_source_color4ub (pick_color->red, pick_color->green, pick_color->blue, pick_color->alpha);

        cogl_path_ellipse (width / 2.0, height / 2.0, width / 2.0, height / 2.0);
        cogl_path_fill ();
#endif
}

/* GObject class and instance initialization functions; note that
 * these have been placed after the Clutter implementation, as
 * they refer to the static function implementations above
 */
/* class init: attach functions to superclasses, define properties
 * and signals
 */
static void iw_circular_node_class_init (IwCircularNodeClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
        GParamSpec *pspec;

        gobject_class->finalize = iw_circular_node_finalize;
        // C++ code is doing that (it makes node square all the time).
        //        actor_class->allocate = iw_circular_node_allocate;
        actor_class->pick = iw_circular_node_pick;

        g_type_class_add_private (klass, sizeof (IwCircularNodePrivate));
}

/* object init: create a private structure and pack
 * composed ClutterActors into it
 */
static void iw_circular_node_init (IwCircularNode *self)
{
        IwCircularNodePrivate *priv = self->priv = IW_CIRCULAR_NODE_GET_PRIVATE (self);

#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self), &c);
#endif

        // priv->layout = clutter_fixed_layout_new ();
        priv->layout = clutter_bin_layout_new (CLUTTER_BIN_ALIGNMENT_CENTER, CLUTTER_BIN_ALIGNMENT_CENTER);
        clutter_actor_set_layout_manager (CLUTTER_ACTOR (self), priv->layout);

        priv->mainCircle = iw_circle_new ();
        clutter_actor_set_reactive (priv->mainCircle, TRUE);
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->mainCircle);

        priv->label = clutter_text_new ();
        //        clutter_text_set_text (CLUTTER_TEXT (priv->label), "A simple test");
        //        clutter_text_set_font_name (CLUTTER_TEXT (priv->label), "22px");
        clutter_text_set_editable (CLUTTER_TEXT (priv->label), FALSE);
        clutter_text_set_selectable (CLUTTER_TEXT (priv->label), FALSE);
        clutter_text_set_single_line_mode (CLUTTER_TEXT (priv->label), TRUE);
        clutter_actor_set_reactive (priv->label, FALSE);
        clutter_actor_set_x_expand (priv->label, TRUE);
        clutter_actor_set_x_align (priv->label, CLUTTER_ACTOR_ALIGN_CENTER);
        clutter_actor_set_y_expand (priv->label, TRUE);
        clutter_actor_set_y_align (priv->label, CLUTTER_ACTOR_ALIGN_CENTER);
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->label);

        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_actor_resize), NULL);
}

/*****************************************************************************/

/// TODO this handler gets called on move, which is inefficient. It should be called only when dimensions are changed.
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data)
{
        IwCircularNodePrivate *priv = IW_CIRCULAR_NODE (actor)->priv;
        float w = clutter_actor_box_get_width (allocation);
        float h = clutter_actor_box_get_height (allocation);
        float d = fmin (w, h);
        clutter_actor_set_size (priv->mainCircle, d, d);
}

/*****************************************************************************/

void iw_circular_node_set_fill_color (IwCircularNode *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        iw_actor_set_fill_color (IW_ACTOR (self->priv->mainCircle), color);
}

/*****************************************************************************/

ClutterColor *iw_circular_node_get_fill_color (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), NULL);
        return iw_actor_get_fill_color (IW_ACTOR (self->priv->mainCircle));
}

/*****************************************************************************/

void iw_circular_node_set_stroke_color (IwCircularNode *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        iw_actor_set_stroke_color (IW_ACTOR (self->priv->mainCircle), color);
}

ClutterColor *iw_circular_node_get_stroke_color (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), NULL);
        return iw_actor_get_stroke_color (IW_ACTOR (self->priv->mainCircle));
}

void iw_circular_node_set_stroke_width (IwCircularNode *self, gfloat w)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        iw_actor_set_stroke_width (IW_ACTOR (self->priv->mainCircle), w);
}

gfloat iw_circular_node_get_stroke_width (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), -1);
        return iw_actor_get_stroke_width (IW_ACTOR (self->priv->mainCircle));
}

void iw_circular_node_set_stroke_dash (IwCircularNode *self, gfloat w)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        iw_actor_set_stroke_dash (IW_ACTOR (self->priv->mainCircle), w);
}

gfloat iw_circular_node_get_stroke_dash (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), -1);
        return iw_actor_get_stroke_dash (IW_ACTOR (self->priv->mainCircle));
}

void iw_circular_node_set_fill (IwCircularNode *self, gboolean b)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        iw_actor_set_fill (IW_ACTOR (self->priv->mainCircle), b);
}

gboolean iw_circular_node_is_fill (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), FALSE);
        return iw_actor_is_fill (IW_ACTOR (self->priv->mainCircle));
}

/*****************************************************************************/

ClutterActor *iw_circular_node_new (void) { return g_object_new (IW_TYPE_CIRCULAR_NODE, NULL); }

/*****************************************************************************/

const gchar *iw_circular_node_get_text (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), NULL);
        return clutter_text_get_text (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_circular_node_set_text (IwCircularNode *self, const gchar *s)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        clutter_text_set_text (CLUTTER_TEXT (self->priv->label), s);
}

/*****************************************************************************/

const gchar *iw_circular_node_get_font (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), NULL);
        return clutter_text_get_font_name (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_circular_node_set_font (IwCircularNode *self, const gchar *s)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        clutter_text_set_font_name (CLUTTER_TEXT (self->priv->label), s);
}

/*****************************************************************************/

void iw_circular_node_get_font_color (IwCircularNode *self, ClutterColor *color)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        return clutter_text_get_color (CLUTTER_TEXT (self->priv->label), color);
}

/*****************************************************************************/

void iw_circular_node_set_font_color (IwCircularNode *self, const ClutterColor *c)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        clutter_text_set_color (CLUTTER_TEXT (self->priv->label), c);
}

/*****************************************************************************/

gboolean iw_circular_node_is_editable (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), FALSE);
        return clutter_text_get_editable (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_circular_node_set_editable (IwCircularNode *self, gboolean b)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        clutter_text_set_editable (CLUTTER_TEXT (self->priv->label), b);
        clutter_text_set_selectable (CLUTTER_TEXT (self->priv->label), b);
        clutter_actor_set_reactive (self->priv->label, b);
}
