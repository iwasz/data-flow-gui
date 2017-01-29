/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IW_BUTTON_H
#define IW_BUTTON_H

#include "iw_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

GType iw_button_get_type (void);

#define IW_TYPE_BUTTON (iw_button_get_type ())
#define IW_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_BUTTON, IwButton))
#define IW_IS_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_BUTTON))
#define IW_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_BUTTON, IwButtonClass))
#define IW_IS_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_BUTTON))
#define IW_BUTTON_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_BUTTON, IwButtonClass))

typedef struct _IwButtonPrivate IwButtonPrivate;
typedef struct _IwButton IwButton;
typedef struct _IwButtonClass IwButtonClass;

struct _IwButton {
        IwActor parent_instance;
        IwButtonPrivate *priv;
};

struct _IwButtonClass {
        void (*clicked) (IwButton *button);
        IwActorClass parent_class;
};

ClutterActor *iw_button_new (void);

const gchar *iw_button_get_text (IwButton *self);
void iw_button_set_text (IwButton *self, const gchar *text);

const gchar *iw_button_get_font (IwButton *self);
void iw_button_set_font (IwButton *self, const gchar *s);

void iw_button_get_font_color (IwButton *self, ClutterColor *color);
void iw_button_set_font_color (IwButton *self, const ClutterColor *c);

void iw_button_set_port_color (IwButton *self, const ClutterColor *color);
void iw_button_set_port_size (IwButton *self, float s);
void iw_button_set_ports_no (IwButton *self);

void iw_button_set_port_user_data (IwButton *self, void *p);
void *iw_button_node_get_port_user_data (IwButton *self);

void iw_button_get_port_position (IwButton *self, float *x, float *y);

#ifdef __cplusplus
}
#endif

#endif // IW_BUTTON_H
