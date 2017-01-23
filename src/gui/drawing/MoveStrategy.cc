/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MoveStrategy.h"
#include "view/IClutterActor.h"
#include "view/ScaleLayer.h"
#include "view/Stage.h"

/*****************************************************************************/

void MoveStrategy::onEnter (Event const &e)
{
        IClutterActor *act;
        if (!(act = dynamic_cast<IClutterActor *> (e.object))) {
                return;
        }

        if (dynamic_cast<ScaleLayer *> (act) || dynamic_cast<Stage *> (act)) {
                return;
        }

        movingActor = act->getActor ();
        dragAction = clutter_drag_action_new ();
        clutter_actor_add_action (movingActor, dragAction);
}

/*****************************************************************************/

void MoveStrategy::onLeave (const Event &e)
{
        if (movingActor) {
                clutter_actor_remove_action (movingActor, dragAction);
                movingActor = nullptr;
        }
}
