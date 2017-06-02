/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef __IW_SIMPLE_DISPLAY_H__
#define __IW_SIMPLE_DISPLAY_H__

#include "iw_abstract_node.h"

#ifdef __cplusplus
extern "C" {
#endif

GType iw_simple_display_get_type (void);

#define IW_TYPE_SIMPLE_DISPLAY (iw_simple_display_get_type ())
#define IW_SIMPLE_DISPLAY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_SIMPLE_DISPLAY, IwSimpleDisplay))
#define IW_IS_SIMPLE_DISPLAY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_SIMPLE_DISPLAY))
#define IW_SIMPLE_DISPLAY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_SIMPLE_DISPLAY, IwSimpleDisplayClass))
#define IW_IS_SIMPLE_DISPLAY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_SIMPLE_DISPLAY))
#define IW_SIMPLE_DISPLAY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_SIMPLE_DISPLAY, IwSimpleDisplayClass))

typedef struct _IwSimpleDisplayPrivate IwSimpleDisplayPrivate;
typedef struct _IwSimpleDisplay IwSimpleDisplay;
typedef struct _IwSimpleDisplayClass IwSimpleDisplayClass;

struct _IwSimpleDisplay {
        IwAbstractNode parent_instance;
        IwSimpleDisplayPrivate *priv;
};

struct _IwSimpleDisplayClass {
        IwAbstractNodeClass parent_class;
};

ClutterActor *iw_simple_display_new (void);

void iw_simple_display_set_text (IwSimpleDisplay *d, const char *text);

#ifdef __cplusplus
}
#endif

#endif /* __IW_SIMPLE_DISPLAY_H__ */
