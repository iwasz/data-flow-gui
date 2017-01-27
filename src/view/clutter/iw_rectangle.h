/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef __IW_RECTANGLE_H__
#define __IW_RECTANGLE_H__

#include "iw_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

GType iw_rectangle_get_type (void);
#define IW_TYPE_RECTANGLE (iw_rectangle_get_type ())
#define IW_RECTANGLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_RECTANGLE, IwRectangle))
#define IW_IS_RECTANGLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_RECTANGLE))
#define IW_RECTANGLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_RECTANGLE, IwRectangleClass))
#define IW_IS_RECTANGLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_RECTANGLE))
#define IW_RECTANGLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_RECTANGLE, IwRectangleClass))

typedef struct _IwRectanglePrivate IwRectanglePrivate;
typedef struct _IwRectangle IwRectangle;
typedef struct _IwRectangleClass IwRectangleClass;

struct _IwRectangle {
        IwActor parent_instance;
        IwRectanglePrivate *priv;
};

struct _IwRectangleClass {
        IwActorClass parent_class;
};

ClutterActor *iw_rectangle_new (void);

#ifdef __cplusplus
}
#endif

#endif /* __IW_RECTANGLE_H__ */
