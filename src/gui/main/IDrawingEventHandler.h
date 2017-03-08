/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDRAWINGEVENTHANDLER_H
#define IDRAWINGEVENTHANDLER_H

#include "Event.h"
#include <ReflectionParserAnnotation.h>
#include <string>

struct __tiliae_reflect__ IDrawingEventHandler {
        virtual ~IDrawingEventHandler () {}
        virtual void pushMessage (std::string const &msg, Event const *event) = 0;
};

#endif // IDRAWINGEVENTHANDLER_H
