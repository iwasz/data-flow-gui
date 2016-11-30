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
#include <vector>
#include <memory>
#include "geometry/Geometry.h"

struct __tiliae_reflect__ IClutterActor : public Core::Object {
        virtual ~IClutterActor () {}

        virtual void setParent (IClutterActor *parent) = 0;
        virtual ClutterActor *getActor () = 0;

        virtual bool getVisible () const = 0;
        virtual void setVisible (bool value) = 0;

        virtual void setPosition (Point const &p) = 0;
        virtual Point getPosition () const = 0;

        virtual void setSize (Dimension const &d) = 0;
        virtual Dimension getDimension () const = 0;

        virtual bool isFill () const = 0;
        virtual void setFill (bool value) = 0;

        virtual float getStrokeWidth () const = 0;
        virtual void setStrokeWidth (float value) = 0;

        virtual float getStrokeDash () const = 0;
        virtual void setStrokeDash (float value) = 0;

        virtual std::string getStrokeColor () const = 0;
        virtual void setStrokeColor (const std::string &value) = 0;

        virtual std::string getFillColor () const = 0;
        virtual void setFillColor (const std::string &value) = 0;
};

typedef std::vector <std::shared_ptr <IClutterActor>> ClutterActorVector;

#endif // ICONTAINER_H
