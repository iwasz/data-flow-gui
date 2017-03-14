/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLUTTER_ICONTAINER_H
#define CLUTTER_ICONTAINER_H

#include "primitives/Color.h"
#include "primitives/Geometry.h"
#include <ReflectionParserAnnotation.h>
#include <clutter-gtk/clutter-gtk.h>
#include <core/Object.h>
#include <core/Typedefs.h>
#include <memory>
#include <string>
#include <vector>

struct __tiliae_reflect__ IClutterActor : public virtual Core::Object {
        virtual ~IClutterActor () {}

        virtual void setParent (IClutterActor *parent) = 0;
        virtual ClutterActor *getActor () = 0;

        virtual bool isVisible () const = 0;
        virtual void setVisible (bool value) = 0;

        virtual bool isSelectable () const = 0;
        virtual void setSelectable (bool value) = 0;

        virtual bool isReactive () const = 0;
        virtual void setReactive (bool value) = 0;

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

        virtual Color getStrokeColor () const = 0;
        virtual void setStrokeColor (const Color &value) = 0;

        virtual Color getFillColor () const = 0;
        virtual void setFillColor (const Color &value) = 0;

        virtual bool isContainter () const = 0;

        virtual Box getBoundingBox () const = 0;
        virtual Point convertToScaleLayer (Point const &p) const = 0;

        virtual Core::StringVector getPropertyViews () const = 0;
};

typedef __tiliae_reflect__ std::vector<IClutterActor *> ClutterActorVector;

#endif // ICONTAINER_H
