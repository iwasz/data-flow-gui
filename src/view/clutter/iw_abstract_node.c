/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_abstract_node.h"
#include "iw_circle.h"
#include "view/clutter/iw_actor.h"
#include <math.h>

/* convenience macro for GType implementations; see:
 * http://library.gnome.org/devel/gobject/2.27/gobject-Type-Information.html#G-DEFINE-TYPE:CAPS
 */
G_DEFINE_TYPE (IwAbstractNode, iw_abstract_node, IW_TYPE_ACTOR);

/* macro for accessing the object's private structure */
#define IW_ABSTRACT_NODE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_ABSTRACT_NODE, IwAbstractNodePrivate))

extern void abstractNodeOnAllocate (void *abstractNode, float x1, float y1, float x2, float y2);

/**
 * One input.
 */
struct _IwAbstractNodePort {
        float x, y;
        ClutterActor *actor;
};

typedef struct _IwAbstractNodePort IwAbstractNodePort;

/*
 * Private structures.
 */
struct _IwAbstractNodePrivate {
//        ClutterLayoutManager *layout;
//        ClutterActor *mainCircle;
//        ClutterActor *label;

        int portsNo;
        IwAbstractNodePort ports[MAX_PORTS_NO];
};

static gboolean do_draw (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data);
static void on_dimension_changed (GObject *gobject, GParamSpec *pspec, gpointer user_data);
static gboolean idle_resize (gpointer data);

/* GObject class and instance initialization functions; note that
 * these have been placed after the Clutter implementation, as
 * they refer to the static function implementations above
 */
/* class init: attach functions to superclasses, define properties
 * and signals
 */
static void iw_abstract_node_class_init (IwAbstractNodeClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        g_type_class_add_private (klass, sizeof (IwAbstractNodePrivate));
}

/*****************************************************************************/

static void iw_abstract_node_init (IwAbstractNode *self)
{
        IwAbstractNodePrivate *priv;

        priv = self->priv = IW_ABSTRACT_NODE_GET_PRIVATE (self);
        priv->portsNo = 0;
        g_signal_connect (CLUTTER_ACTOR (self), "allocation-changed", G_CALLBACK (on_actor_resize), NULL);
}

/*****************************************************************************/

/// TODO this handler gets called on move, which is inefficient. It should be called only when dimensions are changed.
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data)
{
        IwAbstractNodePrivate *priv = IW_ABSTRACT_NODE_GET_PRIVATE (actor);

        float w = clutter_actor_box_get_width (allocation);
        float h = clutter_actor_box_get_height (allocation);
        float d = fmin (w, h);

        for (int i = 0; i < priv->portsNo; ++i) {
                float portR = clutter_actor_get_width (priv->ports[i].actor) / 2.0;
                clutter_actor_set_position (priv->ports[i].actor, priv->ports[i].x * w - portR, priv->ports[i].y * h - portR);
        }

//        clutter_actor_set_size (priv->mainCircle, d, d);
}

/*****************************************************************************/

void iw_abstract_node_get_port_position (IwAbstractNode *self, int i, float *x, float *y)
{
        g_return_if_fail (IW_IS_ABSTRACT_NODE (self));
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

void iw_abstract_node_set_ports_no (IwAbstractNode *self, int i)
{
        g_return_if_fail (IW_IS_ABSTRACT_NODE (self));
        self->priv->portsNo = i;

        for (int i = 0; i < self->priv->portsNo; ++i) {
                ClutterActor *a = self->priv->ports[i].actor = iw_circle_new ();
                iw_actor_set_fill (IW_ACTOR (a), TRUE);
                iw_actor_set_stroke_width (IW_ACTOR (a), 0);
                clutter_actor_add_child (CLUTTER_ACTOR (self), a);
                clutter_actor_set_reactive (a, TRUE);
        }
}

/*****************************************************************************/

void iw_abstract_node_set_port_color (IwAbstractNode *self, int i, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_ABSTRACT_NODE (self));
        iw_actor_set_fill_color (IW_ACTOR (self->priv->ports[i].actor), color);
}

/*****************************************************************************/

void iw_abstract_node_set_port_position (IwAbstractNode *self, int i, float x, float y)
{
        g_return_if_fail (IW_IS_ABSTRACT_NODE (self));
        self->priv->ports[i].x = x;
        self->priv->ports[i].y = y;
}

/*****************************************************************************/

void iw_abstract_node_set_port_size (IwAbstractNode *self, int i, float s)
{
        g_return_if_fail (IW_IS_ABSTRACT_NODE (self));
        g_return_if_fail (i >= 0);
        g_return_if_fail (i < self->priv->portsNo);
        clutter_actor_set_size (CLUTTER_ACTOR (self->priv->ports[i].actor), s, s);
}

/*****************************************************************************/

void iw_abstract_node_set_port_user_data (IwAbstractNode *self, int i, void *p)
{
        g_return_if_fail (IW_IS_ABSTRACT_NODE (self));
        g_object_set_data (G_OBJECT (self->priv->ports[i].actor), CPP_IMPLEMENTATION_KEY, p);
}

/*****************************************************************************/

void *iw_abstract_node_get_port_user_data (IwAbstractNode *self, int i)
{
        g_return_val_if_fail (IW_IS_ABSTRACT_NODE (self), NULL);
        return g_object_get_data (G_OBJECT (self->priv->ports[i].actor), CPP_IMPLEMENTATION_KEY);
}
