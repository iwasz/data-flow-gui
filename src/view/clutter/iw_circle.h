/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef __IW_CIRCLE_H__
#define __IW_CIRCLE_H__

#include "iw_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

GType iw_circle_get_type (void);

#define IW_TYPE_CIRCLE (iw_circle_get_type ())
#define IW_CIRCLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_CIRCLE, IwCircle))
#define IW_IS_CIRCLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_CIRCLE))
#define IW_CIRCLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_CIRCLE, IwCircleClass))
#define IW_IS_CIRCLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_CIRCLE))
#define IW_CIRCLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_CIRCLE, IwCircleClass))

typedef struct _IwCirclePrivate IwCirclePrivate;
typedef struct _IwCircle IwCircle;
typedef struct _IwCircleClass IwCircleClass;

struct _IwCircle {
        IwActor parent_instance;
        IwCirclePrivate *priv;
};

struct _IwCircleClass {
        IwActorClass parent_class;
};

ClutterActor *iw_circle_new (void);

#ifdef __cplusplus
}
#endif

#endif /* __IW_CIRCLE_H__ */
