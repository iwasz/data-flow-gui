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
#include <libavoid.h>

struct IRoutable;

class __tiliae_reflect__ RoutablePin {
public:
        virtual ~RoutablePin () {}

        void init (primitives::Point const &p, IRoutable *owner) __tiliae_no_reflect__;
        //        void setPosition (primitives::Point const &p);

        Avoid::ShapeRef *getShapeRef () __tiliae_no_reflect__;

        void setClassNumber (int i) { classNumber = i; }
        int getClassNumber () const { return classNumber; }

        void setExclusive (bool e) { exclusive = e; }
        bool isExclusive () const { return exclusive; }

private:
        Avoid::ShapeConnectionPin *pin = nullptr;
        IRoutable *owner = nullptr;
        int classNumber = 1;
        bool exclusive = false;
};

#endif // ROUTABLEPIN_H
