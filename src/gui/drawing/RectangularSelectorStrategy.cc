/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RectangularSelectorStrategy.h"
#include "view/Rectangle.h"
#include <clutter/clutter.h>
#include <iostream>

void RectangularSelectorStrategy::onObjectCreated (IClutterActor *a)
{
        Box selectionBox = Box (startPoint, endPoint - startPoint);
        Box minimalSelectionBox;

        // This can be stage, but can be some other container actor (in the future?)
        ClutterActor *stage = clutter_actor_get_parent (rectangularSelector->getActor ());

        for (ClutterActor *child = clutter_actor_get_first_child (stage); child != NULL; child = clutter_actor_get_next_sibling (child)) {

                AbstractActor *actor = static_cast<AbstractActor *> (g_object_get_data (G_OBJECT (child), CPP_IMPLEMENTATION_KEY));

                if (!actor) {
                        continue;
                }

                if (!actor->isVisible () || !actor->isSelectable ()) {
                        continue;
                }

                Box boundingBox = actor->getBoundingBox ();

                if (!boundingBox.isInside (selectionBox)) {
                        continue;
                }

                minimalSelectionBox.resizeContain (boundingBox);
                std::cerr << "[" << typeid (*child).name () << "] " << child << std::endl;
        }

        if (minimalSelectionBox.getDimension () != Dimension ()) {
                rectangularSelector->setPosition (minimalSelectionBox.getA ());
                rectangularSelector->setSize (minimalSelectionBox.getDimension ());
                rectangularSelector->setVisible (true);
        }
        else {
                rectangularSelector->setVisible (false);
        }
}
