/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

/* inclusion guard */
#ifndef __IW_CIRCULAR_NODE_H__
#define __IW_CIRCULAR_NODE_H__

/* include any dependencies */
#include <clutter/clutter.h>
#include "iw_circle.h"

#ifdef __cplusplus
extern "C" {
#endif

/* GObject implementation */

/* declare this function signature to remove compilation errors with -Wall;
 * the iw_circular_node_get_type() function is actually added via the
 * G_DEFINE_TYPE macro in the .c file
 */
GType iw_circular_node_get_type (void);

/* GObject type macros */
/* returns the class type identifier (GType) for IwCircularNode */
#define IW_TYPE_CIRCULAR_NODE (iw_circular_node_get_type ())

/* cast obj to a IwCircularNode object structure*/
#define IW_CIRCULAR_NODE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_CIRCULAR_NODE, IwCircularNode))

/* check whether obj is a IwCircularNode */
#define IW_IS_CIRCULAR_NODE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_CIRCULAR_NODE))

/* cast klass to IwCircularNodeClass class structure */
#define IW_CIRCULAR_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_CIRCULAR_NODE, IwCircularNodeClass))

/* check whether klass is a member of the IwCircularNodeClass */
#define IW_IS_CIRCULAR_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_CIRCULAR_NODE))

/* get the IwCircularNodeClass structure for a IwCircularNode obj */
#define IW_CIRCULAR_NODE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_CIRCULAR_NODE, IwCircularNodeClass))

#define MAX_PORTS_NO 16

/*
 * Private instance fields; see
 * http://www.gotw.ca/gotw/024.htm for the rationale
 */
typedef struct _IwCircularNodePrivate IwCircularNodePrivate;
typedef struct _IwCircularNode IwCircularNode;
typedef struct _IwCircularNodeClass IwCircularNodeClass;

/* object structure */
struct _IwCircularNode {
        /*<private>*/
        ClutterActor parent_instance;

        /* structure containing private members */
        /*<private>*/
        IwCircularNodePrivate *priv;
};

/* class structure */
struct _IwCircularNodeClass {
        /*<private>*/
        ClutterActorClass parent_class;
};

/* public API */

/* constructor - note this returns a ClutterActor instance */
ClutterActor *iw_circular_node_new (void);

// TODO move to base class
void iw_circular_node_set_fill_color (IwCircularNode *self, const ClutterColor *color);
// TODO move to base class
ClutterColor *iw_circular_node_get_fill_color (IwCircularNode *self);

// TODO move to base class
void iw_circular_node_set_stroke_color (IwCircularNode *self, const ClutterColor *color);
// TODO move to base class
ClutterColor *iw_circular_node_get_stroke_color (IwCircularNode *self);

// TODO move to base class
void iw_circular_node_set_stroke_width (IwCircularNode *self, gfloat w);
// TODO move to base class
gfloat iw_circular_node_get_stroke_width (IwCircularNode *self);

// TODO move to base class
void iw_circular_node_set_stroke_dash (IwCircularNode *self, gfloat w);
// TODO move to base class
gfloat iw_circular_node_get_stroke_dash (IwCircularNode *self);

// TODO move to base class
void iw_circular_node_set_fill (IwCircularNode *self, gboolean b);
// TODO move to base class
gboolean iw_circular_node_is_fill (IwCircularNode *self);

void iw_circular_node_set_port_color (IwCircularNode *self, int i, const ClutterColor *color);
// Proportional 0.0 : 1.0
void iw_circular_node_set_port_position (IwCircularNode *self, int i, float x, float y);
void iw_circular_node_set_port_size (IwCircularNode *self, int i, float s);
void iw_circular_node_set_ports_no (IwCircularNode *self, int i);

void iw_circular_node_set_port_user_data (IwCircularNode *self, int i, void *p);
void *iw_circular_node_get_port_user_data (IwCircularNode *self, int i);

void iw_circular_node_get_port_position (IwCircularNode *self, int i, float *x, float *y);

/*---------------------------------------------------------------------------*/

const gchar *iw_circular_node_get_font (IwCircularNode *self);
void iw_circular_node_set_font (IwCircularNode *self, const gchar *s);

void iw_circular_node_get_font_color (IwCircularNode *self, ClutterColor *color);
void iw_circular_node_set_font_color (IwCircularNode *self, const ClutterColor *c);

const gchar *iw_circular_node_get_text (IwCircularNode *self);
void iw_circular_node_set_text (IwCircularNode *self, const gchar *s);

gboolean iw_circular_node_is_editable (IwCircularNode *self);
void iw_circular_node_set_editable (IwCircularNode *self, gboolean b);

/*---------------------------------------------------------------------------*/

//// TODO move to base class
//void iw_circular_node_set_user_data (IwCircularNode *self, void *p);
//// TODO move to base class
//void *iw_circular_node_get_user_data (IwCircularNode *self);

#ifdef __cplusplus
}
#endif

#endif /* __IW_CIRCUlar_nodE_H__ */
