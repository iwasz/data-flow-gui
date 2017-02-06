/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

/* inclusion guard */
#ifndef __IW_CONNECTOR_H__
#define __IW_CONNECTOR_H__

#include "iw_actor.h"
#include "primitives/Direction.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MIN_SEGMENT_LENGTH 50

GType iw_connector_get_type (void);
#define IW_TYPE_CONNECTOR (iw_connector_get_type ())
#define IW_CONNECTOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_CONNECTOR, IwConnector))
#define IW_IS_CONNECTOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_CONNECTOR))
#define IW_CONNECTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_CONNECTOR, IwConnectorClass))
#define IW_IS_CONNECTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_CONNECTOR))
#define IW_CONNECTOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_CONNECTOR, IwConnectorClass))

typedef struct _IwConnectorPrivate IwConnectorPrivate;
typedef struct _IwConnector IwConnector;
typedef struct _IwConnectorClass IwConnectorClass;

struct _IwConnector {
        IwActor parent_instance;
        IwConnectorPrivate *priv;
};

struct _IwConnectorClass {
        IwActorClass parent_class;
};

ClutterActor *iw_connector_new (void);

void iw_connector_set_point_a (IwConnector *self, gfloat x, gfloat y);
void iw_connector_get_point_a (IwConnector *self, gfloat *x, gfloat *y);

void iw_connector_set_point_b (IwConnector *self, gfloat x, gfloat y);
void iw_connector_get_point_b (IwConnector *self, gfloat *x, gfloat *y);

//void iw_connector_set_point_1 (IwConnector *self, gfloat x, gfloat y);
//void iw_connector_get_point_1 (IwConnector *self, gfloat *x, gfloat *y);

//void iw_connector_set_point_2 (IwConnector *self, gfloat x, gfloat y);
//void iw_connector_get_point_2 (IwConnector *self, gfloat *x, gfloat *y);

//void iw_connector_set_point_3 (IwConnector *self, gfloat x, gfloat y);
//void iw_connector_get_point_3 (IwConnector *self, gfloat *x, gfloat *y);

const gchar *iw_connector_get_text (IwConnector *self);
void iw_connector_set_text (IwConnector *self, const gchar *s);

const gchar *iw_connector_get_font (IwConnector *self);
void iw_connector_set_font (IwConnector *self, const gchar *s);

void iw_connector_get_font_color (IwConnector *self, ClutterColor *color);
void iw_connector_set_font_color (IwConnector *self, const ClutterColor *c);

gboolean iw_connector_is_editable (IwConnector *self);
void iw_connector_set_editable (IwConnector *self, gboolean b);

#ifdef __cplusplus
}
#endif

#endif /* __IW_CONNECTOR_H__ */
