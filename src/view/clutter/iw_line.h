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

/* include any dependencies */
#include <clutter/clutter.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GObject implementation */

/* declare this function signature to remove compilation errors with -Wall;
 * the iw_line_get_type() function is actually added via the
 * G_DEFINE_TYPE macro in the .c file
 */
GType iw_line_get_type (void);

/* GObject type macros */
/* returns the class type identifier (GType) for IwLine */
#define IW_TYPE_LINE (iw_line_get_type ())

/* cast obj to a IwLine object structure*/
#define IW_LINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_LINE, IwLine))

/* check whether obj is a IwLine */
#define IW_IS_LINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_LINE))

/* cast klass to IwLineClass class structure */
#define IW_LINE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_LINE, IwLineClass))

/* check whether klass is a member of the IwLineClass */
#define IW_IS_LINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_LINE))

/* get the IwLineClass structure for a IwLine obj */
#define IW_LINE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_LINE, IwLineClass))

/*
 * Private instance fields; see
 * http://www.gotw.ca/gotw/024.htm for the rationale
 */
typedef struct _IwLinePrivate IwLinePrivate;
typedef struct _IwLine IwLine;
typedef struct _IwLineClass IwLineClass;

/* object structure */
struct _IwLine {
        /*<private>*/
        ClutterActor parent_instance;

        /* structure containing private members */
        /*<private>*/
        IwLinePrivate *priv;
};

/* class structure */
struct _IwLineClass {
        /*<private>*/
        ClutterActorClass parent_class;
};

/* public API */

/* constructor - note this returns a ClutterActor instance */
ClutterActor *iw_line_new (void);

void iw_line_set_stroke_color (IwLine *self, const ClutterColor *color);
ClutterColor *iw_line_get_stroke_color (IwLine *self);

void iw_line_set_stroke_width (IwLine *self, gfloat w);
gfloat iw_line_get_stroke_width (IwLine *self);

void iw_line_set_stroke_dash (IwLine *self, gfloat w);
gfloat iw_line_get_stroke_dash (IwLine *self);

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

void iw_line_set_user_data (IwLine *self, void *p);
void *iw_line_get_user_data (IwLine *self);

#ifdef __cplusplus
}
#endif

#endif /* __IW_LINE_H__ */
