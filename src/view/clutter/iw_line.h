/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

/* inclusion guard */
#ifndef __IW_LINE_H__
#define __IW_LINE_H__

#include "iw_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

GType iw_line_get_type (void);
#define IW_TYPE_LINE (iw_line_get_type ())
#define IW_LINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_LINE, IwLine))
#define IW_IS_LINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_LINE))
#define IW_LINE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_LINE, IwLineClass))
#define IW_IS_LINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_LINE))
#define IW_LINE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_LINE, IwLineClass))

typedef struct _IwLinePrivate IwLinePrivate;
typedef struct _IwLine IwLine;
typedef struct _IwLineClass IwLineClass;

struct _IwLine {
        IwActor parent_instance;
        IwLinePrivate *priv;
};

struct _IwLineClass {
        IwActorClass parent_class;
};

ClutterActor *iw_line_new (void);

void iw_line_set_point_a (IwLine *self, gfloat x, gfloat y);
void iw_line_get_point_a (IwLine *self, gfloat *x, gfloat *y);

void iw_line_set_point_b (IwLine *self, gfloat x, gfloat y);
void iw_line_get_point_b (IwLine *self, gfloat *x, gfloat *y);

const gchar *iw_line_get_text (IwLine *self);
void iw_line_set_text (IwLine *self, const gchar *s);

const gchar *iw_line_get_font (IwLine *self);
void iw_line_set_font (IwLine *self, const gchar *s);

void iw_line_get_font_color (IwLine *self, ClutterColor *color);
void iw_line_set_font_color (IwLine *self, const ClutterColor *c);

gboolean iw_line_is_editable (IwLine *self);
void iw_line_set_editable (IwLine *self, gboolean b);

#ifdef __cplusplus
}
#endif

#endif /* __IW_LINE_H__ */
