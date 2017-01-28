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
G_DEFINE_TYPE (IwCircularNode, iw_circular_node, CLUTTER_TYPE_ACTOR);

/* macro for accessing the object's private structure */
#define IW_CIRCULAR_NODE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_CIRCULAR_NODE, IwCircularNodePrivate))

extern void circularNodeOnAllocate (void *circularNode, float x1, float y1, float x2, float y2);

/**
 * One input.
 */
struct _IwCircularNodePort {
        float angle;
        ClutterColor color;
        ClutterActor *actor;
};

typedef struct _IwCircularNodePort IwCircularNodePort;

/*
 * Private structures.
 */
struct _IwCircularNodePrivate {
        ClutterLayoutManager *layout;
        ClutterActor *mainCircle;
        void *userData;

        int portsNo;
        IwCircularNodePort ports[MAX_PORTS_NO];
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

static void iw_circular_node_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags)
{
        IwCircularNodePrivate *priv = IW_CIRCULAR_NODE (actor)->priv;

        /* set the allocation for the whole button */
        //  CLUTTER_ACTOR_CLASS (iw_circular_node_parent_class)->allocate (actor, box, flags);

        ClutterActorBox newBox = *box;
        float dia = fmin (clutter_actor_box_get_width (box), clutter_actor_box_get_height (box));
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
        childBox.x2 = clutter_actor_box_get_width (box);
        childBox.y2 = clutter_actor_box_get_height (box);

        clutter_actor_allocate (priv->mainCircle, &childBox, flags);
        circularNodeOnAllocate (priv->userData, newBox.x1, newBox.y1, newBox.x2, newBox.y2);
}

/*****************************************************************************/

static void iw_circular_node_pick (ClutterActor *actor, const ClutterColor *pick_color)
{

        if (!clutter_actor_should_pick_paint (actor)) {
                return;
        }

        for (ClutterActor *iter = clutter_actor_get_first_child (actor); iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
                clutter_actor_paint (iter);
        }

        //        IwCircularNodePrivate *priv = IW_CIRCULAR_NODE_GET_PRIVATE (actor);
        //        clutter_actor_paint (priv->mainCircle);
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
        actor_class->allocate = iw_circular_node_allocate;
        actor_class->pick = iw_circular_node_pick;

        g_type_class_add_private (klass, sizeof (IwCircularNodePrivate));
}

/* object init: create a private structure and pack
 * composed ClutterActors into it
 */
static void iw_circular_node_init (IwCircularNode *self)
{
        IwCircularNodePrivate *priv;

        priv = self->priv = IW_CIRCULAR_NODE_GET_PRIVATE (self);
        priv->portsNo = 0;

#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color(self, &c);
#endif

        priv->layout = clutter_fixed_layout_new ();

/* the main container; this actor will use the BinLayout to lay
 * out its children; we use the anchor point to keep it centered
 * on the same position even when we change its size
 */
//        priv->box = clutter_actor_new ();
#if 0
        clutter_actor_set_background_color(priv->box, &c);
#endif

        //        clutter_actor_set_layout_manager (priv->box, priv->layout);
        //        clutter_actor_set_reactive (priv->box, TRUE);
        //        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->box);

        priv->mainCircle = iw_circle_new ();
        clutter_actor_set_layout_manager (priv->mainCircle, priv->layout);
        clutter_actor_set_reactive (priv->mainCircle, TRUE);
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->mainCircle);

        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_actor_resize), NULL);

        // TODO This does not work as expected. It gets called when object is moved.
        // g_signal_connect (CLUTTER_ACTOR (self), "notify::width", G_CALLBACK (on_dimension_changed), NULL);
        // g_signal_connect (CLUTTER_ACTOR (self), "notify::height", G_CALLBACK (on_dimension_changed), NULL);
}

/*****************************************************************************/

void on_dimension_changed (GObject *gobject, GParamSpec *pspec, gpointer user_data)
{
        //        gint x_value = 0;

        //        /* Round the X coordinate to the nearest pixel */
        //        x_value = floorf (clutter_actor_get_x (CLUTTER_ACTOR (gobject))) + 0.5;

        //        g_print ("The new X coordinate is '%d' pixels\n", x_value);

        IwCircularNodePrivate *priv = IW_CIRCULAR_NODE_GET_PRIVATE (gobject);

        float w = clutter_actor_get_width (CLUTTER_ACTOR (gobject));
        float h = clutter_actor_get_height (CLUTTER_ACTOR (gobject));
        float d = fmin (w, h);
        float r = d / 2;

        for (int i = 0; i < priv->portsNo; ++i) {
                float portR = clutter_actor_get_width (priv->ports[i].actor) / 2.0;
                clutter_actor_set_position (priv->ports[i].actor, r * cos (priv->ports[i].angle) + r - portR, r * sin (priv->ports[i].angle) + r - portR);
        }

        clutter_actor_set_size (priv->mainCircle, d, d);
}

/*****************************************************************************/

/// TODO this handler gets called on move, which is inefficient. It should be called only when dimensions are changed.
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data)
{
        //        clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)), ceilf (clutter_actor_box_get_width (allocation)),
        //                                 ceilf (clutter_actor_box_get_height (allocation)));

        IwCircularNodePrivate *priv = IW_CIRCULAR_NODE_GET_PRIVATE (actor);

        float w = clutter_actor_box_get_width (allocation);
        float h = clutter_actor_box_get_height (allocation);
        float d = fmin (w, h);
        float r = d / 2;

        for (int i = 0; i < priv->portsNo; ++i) {
                float portR = clutter_actor_get_width (priv->ports[i].actor) / 2.0;
                clutter_actor_set_position (priv->ports[i].actor, r * cos (priv->ports[i].angle) + r - portR, r * sin (priv->ports[i].angle) + r - portR);
        }

        clutter_actor_set_size (priv->mainCircle, d, d);
}

/*****************************************************************************/

void iw_circular_node_get_port_position (IwCircularNode *self, int i, float *x, float *y)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        float px, py;
        ClutterActor *port = self->priv->ports[i].actor;
        clutter_actor_get_position (port, &px, &py);

        px += clutter_actor_get_width (port) / 2.0;
        py += clutter_actor_get_height (port) / 2.0;

        float ax, ay;
        clutter_actor_get_position (CLUTTER_ACTOR (self), &ax, &ay);

        *x = px + ax;
        *y = py + ay;
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

static gboolean portMotionEvent (ClutterActor *actor, ClutterEvent *event, gpointer user_data) { return CLUTTER_EVENT_STOP; }

void iw_circular_node_set_ports_no (IwCircularNode *self, int i)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        self->priv->portsNo = i;

        for (int i = 0; i < self->priv->portsNo; ++i) {
                ClutterActor *a = self->priv->ports[i].actor = iw_circle_new ();
                iw_actor_set_fill (IW_ACTOR (a), TRUE);
                iw_actor_set_stroke_width (IW_ACTOR (a), 0);
                clutter_actor_add_child (CLUTTER_ACTOR (self->priv->mainCircle), a);
                clutter_actor_set_reactive (a, TRUE);
        }
}

/*****************************************************************************/

void iw_circular_node_set_port_color (IwCircularNode *self, int i, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        iw_actor_set_fill_color (IW_ACTOR (self->priv->ports[i].actor), color);
}

/*****************************************************************************/

void iw_circular_node_set_port_angle (IwCircularNode *self, int i, float angle)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        self->priv->ports[i].angle = angle;
}

/*****************************************************************************/

void iw_circular_node_set_port_size (IwCircularNode *self, int i, float s)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        g_return_if_fail (i >= 0);
        g_return_if_fail (i < self->priv->portsNo);
        //        self->priv->ports[i].size = s;
        //        clutter_content_invalidate (self->priv->canvas);
        clutter_actor_set_size (CLUTTER_ACTOR (self->priv->ports[i].actor), s, s);
}

/*****************************************************************************/

ClutterActor *iw_circular_node_new (void) { return g_object_new (IW_TYPE_CIRCULAR_NODE, NULL); }

/*****************************************************************************/

void iw_circular_node_set_user_data (IwCircularNode *self, void *p)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        self->priv->userData = p;
}

/*****************************************************************************/

void *iw_circular_node_get_user_data (IwCircularNode *self)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), NULL);
        return self->priv->userData;
}

/*****************************************************************************/

void iw_circular_node_set_port_user_data (IwCircularNode *self, int i, void *p)
{
        g_return_if_fail (IW_IS_CIRCULAR_NODE (self));
        g_object_set_data (G_OBJECT (self->priv->ports[i].actor), CPP_IMPLEMENTATION_KEY, p);
}

/*****************************************************************************/

void *iw_circular_node_get_port_user_data (IwCircularNode *self, int i)
{
        g_return_val_if_fail (IW_IS_CIRCULAR_NODE (self), NULL);
        return g_object_get_data (G_OBJECT (self->priv->ports[i].actor), CPP_IMPLEMENTATION_KEY);
}
