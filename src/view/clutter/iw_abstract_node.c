/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_abstract_node.h"
#include "iw_ellipse.h"
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
        int portsNo;
        IwAbstractNodePort ports[MAX_PORTS_NO];
        ClutterActor *portLayer;
        ClutterLayoutManager *layout;
};

static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data);

/*****************************************************************************/

static void iw_abstract_node_class_init (IwAbstractNodeClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        g_type_class_add_private (klass, sizeof (IwAbstractNodePrivate));
}

/*****************************************************************************/

static void iw_abstract_node_init (IwAbstractNode *self)
{
        IwAbstractNodePrivate *priv = self->priv = IW_ABSTRACT_NODE_GET_PRIVATE (self);

        // This does not work, causing ports to be displayed incorrectly (not clipped, but kind of resized, and offset).
        // GValue gVal = G_VALUE_INIT;
        // g_value_init (&gVal, CLUTTER_TYPE_RECT);
        // g_value_set_boxed (&gVal, NULL);
        // g_object_set_property (G_OBJECT (self), "clip-rect", &gVal);
        // g_value_unset (&gVal);

        // This helps.
        priv->layout = clutter_bin_layout_new (CLUTTER_BIN_ALIGNMENT_CENTER, CLUTTER_BIN_ALIGNMENT_CENTER);
        clutter_actor_set_layout_manager (CLUTTER_ACTOR (self), priv->layout);

        priv->portsNo = 0;
        priv->portLayer = clutter_actor_new ();
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->portLayer);
#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (priv->portLayer, &c);
#endif

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
                float portX = priv->ports[i].x * w - portR;
                float portY = priv->ports[i].y * h - portR;
                //                printf ("port [%d], %f, %f\n", i, portX, portY);
                clutter_actor_set_position (priv->ports[i].actor, portX, portY);
        }

        //        clutter_actor_set_position (priv->portLayer, allocation->x1 - 10, allocation->y1 - 10);
        //        clutter_actor_set_size (priv->portLayer, w + 10, h + 10);
        //        clutter_actor_set_position (priv->portLayer, -10, -10);
        clutter_actor_set_size (priv->portLayer, w, h);
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
                ClutterActor *a = self->priv->ports[i].actor = iw_ellipse_new ();
                iw_actor_set_fill (IW_ACTOR (a), TRUE);
                iw_actor_set_stroke_width (IW_ACTOR (a), 0);
                clutter_actor_add_child (CLUTTER_ACTOR (self->priv->portLayer), a);
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
