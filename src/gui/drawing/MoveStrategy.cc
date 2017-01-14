/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "view/IClutterActor.h"
#include "view/Stage.h"
#include "MoveStrategy.h"

/*****************************************************************************/

void MoveStrategy::onEnter (Point p, Core::Object *o)
{
        IClutterActor *act;
        if (!(act = dynamic_cast<IClutterActor *> (o))) {
                return;
        }

        if (dynamic_cast<Stage *> (act)) {
                return;
        }

        movingActor = act->getActor ();
        dragAction = clutter_drag_action_new ();
        clutter_actor_add_action (movingActor, dragAction);
}

/*****************************************************************************/

void MoveStrategy::onLeave (Point p, Core::Object *o)
{
        if (movingActor) {
                clutter_actor_remove_action (movingActor, dragAction);
                movingActor = nullptr;
        }
}
