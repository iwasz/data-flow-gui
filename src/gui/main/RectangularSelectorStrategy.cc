/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RectangularSelectorStrategy.h"
#include "view/Rectangle.h"
#include "view/ScaleLayer.h"
#include "view/clutter/iw_actor.h"
#include <clutter/clutter.h>
#include <iostream>

/*****************************************************************************/

void RectangularSelectorStrategy::onObjectCreated (IClutterActor *) { onObjectCreated (nullptr, true); }

/*****************************************************************************/

void RectangularSelectorStrategy::onObjectCreated (IClutterActor *, bool inside)
{
        primitives::Box selectionBox = primitives::Box (startPoint, endPoint - startPoint);
        primitives::Box minimalSelectionBox;

        ClutterActor *root = scaleLayer->getActor ();

        for (ClutterActor *child = clutter_actor_get_first_child (root); child != NULL; child = clutter_actor_get_next_sibling (child)) {

                IClutterActor *actor = static_cast<IClutterActor *> (g_object_get_data (G_OBJECT (child), CPP_IMPLEMENTATION_KEY));

                if (!actor) {
                        continue;
                }

                if (!actor->isVisible () || !actor->isSelectable ()) {
                        continue;
                }

                primitives::Box boundingBox = actor->getBoundingBox ();

                if (inside) {
                        if (!boundingBox.isInside (selectionBox)) {
                                continue;
                        }
                }
                else {
                        if (!boundingBox.isIntersects (selectionBox)) {
                                continue;
                        }
                }

                minimalSelectionBox.resizeContain (boundingBox);
                selectedActors->push_back (actor);
        }

        if (minimalSelectionBox.getDimension () != primitives::Dimension ()) {
                rectangularSelector->setPosition (minimalSelectionBox.getA ());
                rectangularSelector->setSize (minimalSelectionBox.getDimension ());
                rectangularSelector->setVisible (true);

//                for (IClutterActor *actor : *selectedActors) {
//                        actor->setParent (rectangularSelector);
//                        primitives::Point pos = actor->getPosition ();
//                        pos.x -= minimalSelectionBox.getA ().x;
//                        pos.y -= minimalSelectionBox.getA ().y;
//                        actor->setPosition (pos);
//                }
        }
        else {
                rectangularSelector->setVisible (false);
        }
}

/*****************************************************************************/

void RectangularSelectorStrategy::onButtonPress (const Event &e)
{
        unselectAll ();
        ShapeDrawStrategy::onButtonPress (e);
}

/*****************************************************************************/

void RectangularSelectorStrategy::unselectAll ()
{
        rectangularSelector->setVisible (false);

        // This can be stage, but can be some other container actor (in the future?)
        ClutterActor *stage = clutter_actor_get_parent (rectangularSelector->getActor ());
        IClutterActor *stageActor = static_cast<IClutterActor *> (g_object_get_data (G_OBJECT (stage), CPP_IMPLEMENTATION_KEY));

        primitives::Point selectionRectanglePosition = rectangularSelector->getPosition ();

//        for (IClutterActor *actor : *selectedActors) {
//                actor->setParent (stageActor);
//                primitives::Point pos = actor->getPosition ();
//                pos.x += selectionRectanglePosition.x;
//                pos.y += selectionRectanglePosition.y;
//                actor->setPosition (pos);
//        }

        selectedActors->clear ();
}
