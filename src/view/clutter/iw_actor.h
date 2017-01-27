/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef __IW_ACTOR_H__
#define __IW_ACTOR_H__

#include <clutter/clutter.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CPP_IMPLEMENTATION_KEY "cppImplKey"

/* GObject implementation */

/* declare this function signature to remove compilation errors with -Wall;
 * the iw_actor_get_type() function is actually added via the
 * G_DEFINE_TYPE macro in the .c file
 */
GType iw_actor_get_type (void);

/* GObject type macros */
/* returns the class type identifier (GType) for IwActor */
#define IW_TYPE_ACTOR (iw_actor_get_type ())

/* cast obj to a IwActor object structure*/
#define IW_ACTOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), IW_TYPE_ACTOR, IwActor))

/* check whether obj is a IwActor */
#define IW_IS_ACTOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IW_TYPE_ACTOR))

/* cast klass to IwActorClass class structure */
#define IW_ACTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), IW_TYPE_ACTOR, IwActorClass))

/* check whether klass is a member of the IwActorClass */
#define IW_IS_ACTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), IW_TYPE_ACTOR))

/* get the IwActorClass structure for a IwActor obj */
#define IW_ACTOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), IW_TYPE_ACTOR, IwActorClass))

/*
 * Private instance fields; see
 * http://www.gotw.ca/gotw/024.htm for the rationale
 */
typedef struct _IwActorPrivate IwActorPrivate;
typedef struct _IwActor IwActor;
typedef struct _IwActorClass IwActorClass;

/* object structure */
struct _IwActor {
        /*<private>*/
        ClutterActor parent_instance;

        /* structure containing private members */
        /*<private>*/
        IwActorPrivate *priv;
};

/* class structure */
struct _IwActorClass {
        /*<private>*/
        ClutterActorClass parent_class;
};

/* public API */

/* constructor - note this returns a ClutterActor instance */
//ClutterActor *iw_actor_new (void);

void iw_actor_set_fill_color (IwActor *self, const ClutterColor *color);
ClutterColor *iw_actor_get_fill_color (IwActor *self);

void iw_actor_set_stroke_color (IwActor *self, const ClutterColor *color);
ClutterColor *iw_actor_get_stroke_color (IwActor *self);

void iw_actor_set_stroke_width (IwActor *self, gfloat w);
gfloat iw_actor_get_stroke_width (IwActor *self);

void iw_actor_set_stroke_dash (IwActor *self, gfloat w);
gfloat iw_actor_get_stroke_dash (IwActor *self);

void iw_actor_set_fill (IwActor *self, gboolean b);
gboolean iw_actor_is_fill (IwActor *self);

void iw_actor_set_user_data (IwActor *self, void *p);
void *iw_actor_get_user_data (IwActor *self);

ClutterContent *iw_actor_get_canvas (IwActor *self);

#ifdef __cplusplus
}
#endif

#endif /* __IW_ACTOR_H__ */
