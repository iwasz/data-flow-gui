/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IROUTABLE_H
#define IROUTABLE_H

#include "primitives/Direction.h"
#include "primitives/Geometry.h"
#include <ReflectionParserAnnotation.h>
#include <libavoid/libavoid.h>

class RoutablePin;

/// Interface for all callbacks. One common interface to simplify things.
struct __tiliae_reflect__ IRoutableObserver : public virtual Core::Object {
        virtual ~IRoutableObserver () {}
        // TODO change parameter to some polygon
        virtual void onReroute (Avoid::ConnRef *) __tiliae_no_reflect__ = 0;
};

/// Wide interface to describe all routable objects.
struct __tiliae_reflect__ IRoutable : public virtual Core::Object {
        virtual ~IRoutable () {}

        virtual void init (primitives::Point const &p, primitives::Dimension const &d, IRoutableObserver *o = nullptr) __tiliae_no_reflect__ = 0;

        virtual Avoid::Router *getRouter () __tiliae_no_reflect__ = 0;
        virtual void setRouter (Avoid::Router *r) __tiliae_no_reflect__ = 0;
        virtual Avoid::ShapeRef *getShapeRef () __tiliae_no_reflect__ = 0;

        // TODO remove
        virtual bool isRouting () const = 0;

        virtual primitives::Point getPosition () const __tiliae_no_reflect__ = 0;
        virtual void setPosition (primitives::Point const &p) __tiliae_no_reflect__ = 0;
        virtual void move (primitives::Dimension const &d) __tiliae_no_reflect__ = 0;
        virtual void setSize (primitives::Dimension const &d) __tiliae_no_reflect__ = 0;

        virtual void setObserver (IRoutableObserver *o) __tiliae_no_reflect__ = 0;
        virtual IRoutableObserver *getObserver () __tiliae_no_reflect__ = 0;

        virtual void connect (RoutablePin *pin, Side s) __tiliae_no_reflect__ = 0;
};

#endif // IROUTABLE_H
