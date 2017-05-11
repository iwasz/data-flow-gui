/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTROUTABLE_H
#define ABSTRACTROUTABLE_H

#include "IRoutable.h"

class __tiliae_reflect__ AbstractRoutable : public IRoutable {
public:
        virtual ~AbstractRoutable ();

        virtual void init (primitives::Point const &p, primitives::Dimension const &d, IRoutableObserver *o = nullptr) __tiliae_no_reflect__;

        virtual Avoid::Router *getRouter () __tiliae_no_reflect__ { return router; }
        virtual Avoid::ShapeRef *getShapeRef () __tiliae_no_reflect__ { return shapeRef; }

        virtual bool isRouting () const { return routing; }
        virtual void setRouting (bool value) { routing = value; }

        virtual void setParent (IRoutable *parent) __tiliae_no_reflect__ { router = parent->getRouter (); }

        virtual primitives::Point getPosition () const __tiliae_no_reflect__;
        virtual void setPosition (primitives::Point const &p) __tiliae_no_reflect__;
        virtual void move (primitives::Dimension const &d) __tiliae_no_reflect__;
        virtual void setSize (primitives::Dimension const &d) __tiliae_no_reflect__;

        virtual void setObserver (IRoutableObserver *o) __tiliae_no_reflect__ { observer = o; }
        virtual IRoutableObserver *getObserver () __tiliae_no_reflect__ { return observer; }

        virtual void connect (RoutablePin *pin, Side s) __tiliae_no_reflect__ {}

private:
        bool routing = false;
        Avoid::Router *router = nullptr;
        Avoid::ShapeRef *shapeRef = nullptr;
        IRoutableObserver *observer = nullptr;
};

#endif // ABSTRACTROUTABLE_H
