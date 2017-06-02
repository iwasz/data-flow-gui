/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

/* inclusion guard */
#ifndef __IW_ABSTRACT_NODE_H__
#define __IW_ABSTRACT_NODE_H__

/* include any dependencies */
#include "iw_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* GObject implementation */

/* declare this function signature to remove compilation errors with -Wall;
 * the iw_abstract_node_get_type() function is actually added via the
 * G_DEFINE_TYPE macro in the .c file
 */
GType iw_abstract_node_get_type (void);

/* GObject type macros */
/* returns the class type identifier (GType) for IwAbstractNode */
#define IW_TYPE_ABSTRACT_NODE (iw_abstract_node_get_type ())

/* cast obj to a IwAbstractNode object structure*/
#define IW_ABSTRACT_NODE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_ABSTRACT_NODE, IwAbstractNode))

/* check whether obj is a IwAbstractNode */
#define IW_IS_ABSTRACT_NODE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_ABSTRACT_NODE))

/* cast klass to IwAbstractNodeClass class structure */
#define IW_ABSTRACT_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_ABSTRACT_NODE, IwAbstractNodeClass))

/* check whether klass is a member of the IwAbstractNodeClass */
#define IW_IS_ABSTRACT_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_ABSTRACT_NODE))

/* get the IwAbstractNodeClass structure for a IwAbstractNode obj */
#define IW_ABSTRACT_NODE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_ABSTRACT_NODE, IwAbstractNodeClass))

#define MAX_PORTS_NO 16

/*
 * Private instance fields; see
 * http://www.gotw.ca/gotw/024.htm for the rationale
 */
typedef struct _IwAbstractNodePrivate IwAbstractNodePrivate;
typedef struct _IwAbstractNode IwAbstractNode;
typedef struct _IwAbstractNodeClass IwAbstractNodeClass;

/* object structure */
struct _IwAbstractNode {
        /*<private>*/
        IwActor parent_instance;

        /* structure containing private members */
        /*<private>*/
        IwAbstractNodePrivate *priv;
};

/* class structure */
struct _IwAbstractNodeClass {
        /*<private>*/
        IwActorClass parent_class;
};

/* public API */

/* constructor - note this returns a ClutterActor instance */
ClutterActor *iw_abstract_node_new (void);

void iw_abstract_node_set_port_color (IwAbstractNode *self, int i, const ClutterColor *color);
/// Proportional 0.0 : 1.0
void iw_abstract_node_set_port_position (IwAbstractNode *self, int i, float x, float y);
void iw_abstract_node_set_port_size (IwAbstractNode *self, int i, float s);
void iw_abstract_node_set_ports_no (IwAbstractNode *self, int i);

void iw_abstract_node_set_port_user_data (IwAbstractNode *self, int i, void *p);
void *iw_abstract_node_get_port_user_data (IwAbstractNode *self, int i);

void iw_abstract_node_get_port_position (IwAbstractNode *self, int i, float *x, float *y);

#ifdef __cplusplus
}
#endif

#endif /* __IW_abstract_nodE_H__ */
