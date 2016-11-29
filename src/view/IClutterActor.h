/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLUTTER_ICONTAINER_H
#define CLUTTER_ICONTAINER_H

#include <core/Object.h>
#include <ReflectionParserAnnotation.h>
#include <clutter-gtk/clutter-gtk.h>
#include <string>

struct __tiliae_reflect__ IClutterActor : public Core::Object {
        virtual ~IClutterActor () {}
        virtual ClutterActor *getActor () = 0;
};

#endif // ICONTAINER_H
