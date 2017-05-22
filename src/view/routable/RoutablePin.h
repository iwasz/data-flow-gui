/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ROUTABLEPIN_H
#define ROUTABLEPIN_H

#include "primitives/Geometry.h"
#include <ReflectionParserAnnotation.h>
#include <core/variant/Variant.h>
#include <libavoid.h>
#include <string>

struct IRoutable;

class __tiliae_reflect__ RoutablePin {
public:
        virtual ~RoutablePin () {}

        void init (primitives::Point const &p, IRoutable *owner) __tiliae_no_reflect__;

        Avoid::ShapeRef *getShapeRef () __tiliae_no_reflect__;

        void setClassNumber (int i) { classNumber = i; }
        int getClassNumber () const { return classNumber; }

        void setExclusive (bool e) { exclusive = e; }
        bool isExclusive () const { return exclusive; }

        bool isRelative () const { return relative; }
        void setRelative (bool value) { relative = value; }

        double getInsideOffset () const { return insideOffset; }
        void setInsideOffset (double value) { insideOffset = value; }

        Avoid::ConnDirFlag getDirection () const { return direction; }
        void setDirection (const Avoid::ConnDirFlag &value) { direction = value; }

private:
        Avoid::ShapeConnectionPin *pin = nullptr;
        IRoutable *owner = nullptr;
        int classNumber = 1;
        bool exclusive = false;
        bool relative = true;
        double insideOffset = 0;
        Avoid::ConnDirFlag direction = Avoid::ConnDirAll;
};

/**
 * @brief avoidDirectionFromString Conversion for IoC.
 * @param s
 * @return
 */
extern Core::Variant avoidDirectionFromString (std::string const &s);

#endif // ROUTABLEPIN_H
