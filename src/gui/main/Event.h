/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_DRAWING_EVENT_H
#define DATA_FLOW_DRAWING_EVENT_H

#include <clutter/clutter.h>
#include <core/Object.h>
#include <primitives/Geometry.h>
#include <string>

/**
 * Additional arguments for state machine. Pointer to this struct is passed
 * whenever I need some additional data in the state machine actions.
 */
struct Event {
        std::string tool;
        primitives::Point positionStageCoords;
        primitives::Point positionParentCoords;
        Core::Object *object = nullptr;
        int button = -1;
        unsigned int key = 0;
        ClutterModifierType state;
        bool shiftPressed = false;
        bool ctrlPressed = false;
        ClutterScrollDirection scrollDirection;
        double scrollX = 0;
        double scrollY = 0;
        primitives::Dimension stageDelta;
        primitives::Dimension parentDelta;
};

#endif // EVENT_H
