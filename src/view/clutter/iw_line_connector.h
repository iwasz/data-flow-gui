/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#if 0
/* inclusion guard */
#ifndef __IW_LINE_CONNECTOR_CONNECTOR_H__
#define __IW_LINE_CONNECTOR_CONNECTOR_H__

/* include any dependencies */
#include <clutter/clutter.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GObject implementation */

/* declare this function signature to remove compilation errors with -Wall;
 * the iw_line_connector_get_type() function is actually added via the
 * G_DEFINE_TYPE macro in the .c file
 */
GType iw_line_connector_get_type (void);

/* GObject type macros */
/* returns the class type identifier (GType) for IwLineConnector */
#define IW_TYPE_LINE_CONNECTOR (iw_line_connector_get_type ())

/* cast obj to a IwLineConnector object structure*/
#define IW_LINE_CONNECTOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_LINE_CONNECTOR, IwLineConnector))

/* check whether obj is a IwLineConnector */
#define IW_IS_LINE_CONNECTOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_LINE_CONNECTOR))

/* cast klass to IwLineConnectorClass class structure */
#define IW_LINE_CONNECTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_LINE_CONNECTOR, IwLineConnectorClass))

/* check whether klass is a member of the IwLineConnectorClass */
#define IW_IS_LINE_CONNECTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_LINE_CONNECTOR))

/* get the IwLineConnectorClass structure for a IwLineConnector obj */
#define IW_LINE_CONNECTOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_LINE_CONNECTOR, IwLineConnectorClass))

/*
 * Private instance fields; see
 * http://www.gotw.ca/gotw/024.htm for the rationale
 */
typedef struct _IwLineConnectorPrivate IwLineConnectorPrivate;
typedef struct _IwLineConnector IwLineConnector;
typedef struct _IwLineConnectorClass IwLineConnectorClass;

/* object structure */
struct _IwLineConnector {
        /*<private>*/
        ClutterActor parent_instance;

        /* structure containing private members */
        /*<private>*/
        IwLineConnectorPrivate *priv;
};

/* class structure */
struct _IwLineConnectorClass {
        /*<private>*/
        ClutterActorClass parent_class;
};

/* public API */

/* constructor - note this returns a ClutterActor instance */
ClutterActor *iw_line_connector_new (void);

void iw_line_connector_set_stroke_color (IwLineConnector *self, const ClutterColor *color);
ClutterColor *iw_line_connector_get_stroke_color (IwLineConnector *self);

void iw_line_connector_set_stroke_width (IwLineConnector *self, gfloat w);
gfloat iw_line_connector_get_stroke_width (IwLineConnector *self);

void iw_line_connector_set_stroke_dash (IwLineConnector *self, gfloat w);
gfloat iw_line_connector_get_stroke_dash (IwLineConnector *self);

void iw_line_connector_set_point_a (IwLineConnector *self, gfloat x, gfloat y);
void iw_line_connector_get_point_a (IwLineConnector *self, gfloat *x, gfloat *y);

void iw_line_connector_set_point_b (IwLineConnector *self, gfloat x, gfloat y);
void iw_line_connector_get_point_b (IwLineConnector *self, gfloat *x, gfloat *y);

#ifdef __cplusplus
}
#endif

#endif /* __IW_LINE_CONNECTOR_H__ */
#endif
