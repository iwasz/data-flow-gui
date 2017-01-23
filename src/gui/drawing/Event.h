/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_DRAWING_EVENT_H
#define DATA_FLOW_DRAWING_EVENT_H

#include <core/Object.h>
#include <primitives/Geometry.h>
#include <string>

/**
 * Additional arguments for state machine. Pointer to this struct is passed
 * whenever I need some additional data in the state machine actions.
 */
struct Event {
        std::string tool;
        Point positionStageCoords;
        Point positionParentCoords;
        Core::Object *object = nullptr;
        int button = -1;
};

#endif // EVENT_H
