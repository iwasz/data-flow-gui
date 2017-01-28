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

GType cb_button_get_type (void);

#define CB_TYPE_BUTTON (cb_button_get_type ())
#define CB_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CB_TYPE_BUTTON, CbButton))
#define CB_IS_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CB_TYPE_BUTTON))
#define CB_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CB_TYPE_BUTTON, CbButtonClass))
#define CB_IS_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CB_TYPE_BUTTON))
#define CB_BUTTON_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CB_TYPE_BUTTON, CbButtonClass))

typedef struct _CbButtonPrivate CbButtonPrivate;
typedef struct _CbButton CbButton;
typedef struct _CbButtonClass CbButtonClass;

struct _CbButton {
        IwActor parent_instance;
        CbButtonPrivate *priv;
};

struct _CbButtonClass {
        void (*clicked) (CbButton *button);
        IwActorClass parent_class;
};

ClutterActor *cb_button_new (void);

const gchar *cb_button_get_text (CbButton *self);
void cb_button_set_text (CbButton *self, const gchar *text);

void cb_button_set_text_color (CbButton *self, const ClutterColor *color);

#ifdef __cplusplus
}
#endif

#endif // IW_BUTTON_H
