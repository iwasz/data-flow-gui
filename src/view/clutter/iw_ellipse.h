/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef __IW_ELLIPSE_H__
#define __IW_ELLIPSE_H__

#include "iw_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

GType iw_ellipse_get_type (void);

#define IW_TYPE_ELLIPSE (iw_ellipse_get_type ())
#define IW_ELLIPSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_ELLIPSE, IwEllipse))
#define IW_IS_ELLIPSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_ELLIPSE))
#define IW_ELLIPSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_ELLIPSE, IwEllipseClass))
#define IW_IS_ELLIPSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_ELLIPSE))
#define IW_ELLIPSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_ELLIPSE, IwEllipseClass))

typedef struct _IwEllipsePrivate IwEllipsePrivate;
typedef struct _IwEllipse IwEllipse;
typedef struct _IwEllipseClass IwEllipseClass;

struct _IwEllipse {
        IwActor parent_instance;
        IwEllipsePrivate *priv;
};

struct _IwEllipseClass {
        IwActorClass parent_class;
};

ClutterActor *iw_ellipse_new (void);

#ifdef __cplusplus
}
#endif

#endif /* __IW_ELLIPSE_H__ */
