/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef __IW_RECTANGLE_H__
#define __IW_RECTANGLE_H__

#include <clutter/clutter.h>

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

// Object structure
struct _IwRectangle {
        /*<private>*/
        ClutterActor parent_instance;

        /* structure containing private members */
        /*<private>*/
        IwRectanglePrivate *priv;
};

/* class structure */
struct _IwRectangleClass {
        /*<private>*/
        ClutterActorClass parent_class;
};

/* public API */

/* constructor - note this returns a ClutterActor instance */
ClutterActor *iw_rectangle_new (void);

void iw_rectangle_set_fill_color (IwRectangle *self, const ClutterColor *color);
ClutterColor *iw_rectangle_get_fill_color (IwRectangle *self);

void iw_rectangle_set_stroke_color (IwRectangle *self, const ClutterColor *color);
ClutterColor *iw_rectangle_get_stroke_color (IwRectangle *self);

void iw_rectangle_set_stroke_width (IwRectangle *self, gfloat w);
gfloat iw_rectangle_get_stroke_width (IwRectangle *self);

void iw_rectangle_set_stroke_dash (IwRectangle *self, gfloat w);
gfloat iw_rectangle_get_stroke_dash (IwRectangle *self);

void iw_rectangle_set_fill (IwRectangle *self, gboolean b);
gboolean iw_rectangle_is_fill (IwRectangle *self);

#ifdef __cplusplus
}
#endif

#endif /* __IW_RECTANGLE_H__ */
