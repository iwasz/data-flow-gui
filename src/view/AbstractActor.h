/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTACTOR_H
#define ABSTRACTACTOR_H

#include "IClutterActor.h"
#include <core/Exception.h>

extern "C" void abstractActorOnFinalize (void *ptr);

/**
 * Runs in IClutterActor::setSize, and modifies passed dimension it.
 * May be applied to its owner and other ICluterActors as well.
 */
struct __tiliae_reflect__ ISizeConstraint : public Core::Object {
        virtual ~ISizeConstraint () {}

        virtual primitives::Dimension run (primitives::Dimension const &d) const __tiliae_no_reflect__ = 0;
};

class __tiliae_reflect__ AbstractSizeConstraint : public ISizeConstraint {
public:
        virtual ~AbstractSizeConstraint () {}

        primitives::Dimension run (primitives::Dimension const &d0) const __tiliae_no_reflect__;
        virtual primitives::Dimension runImpl (primitives::Dimension const &d) const __tiliae_no_reflect__ = 0;

        AbstractSizeConstraint const *getNext () const { return next; }
        void setNext (AbstractSizeConstraint *value) { next = value; }

private:
        AbstractSizeConstraint *next = nullptr;
};

class __tiliae_reflect__ SquareSizeConstraint : public AbstractSizeConstraint {
public:
        virtual ~SquareSizeConstraint () {}
        virtual primitives::Dimension runImpl (primitives::Dimension const &d) const __tiliae_no_reflect__;
};

class __tiliae_reflect__ MinSizeConstraint : public AbstractSizeConstraint {
public:
        virtual ~MinSizeConstraint () {}
};

class __tiliae_reflect__ MaxSizeConstraint : public AbstractSizeConstraint {
public:
        virtual ~MaxSizeConstraint () {}
};

/**
 * @brief The AbstractActor class
 */
class __tiliae_reflect__ AbstractActor : public IClutterActor, public IRoutableObserver {
public:
        virtual void init ();
        virtual ~AbstractActor ();

        virtual void setParent (IClutterActor *parent);
        virtual ClutterActor *getActor () { return self; }

        virtual bool isVisible () const;
        virtual void setVisible (bool value);

        virtual bool isSelectable () const { return selectable; }
        virtual void setSelectable (bool value) { selectable = value; }

        virtual bool isReactive () const;
        virtual void setReactive (bool value);

        virtual void setPosition (primitives::Point const &p);
        virtual void move (primitives::Dimension const &d);
        virtual primitives::Point getPosition () const;
        virtual primitives::Point getScaleLayerPosition () const;

        virtual void setSize (primitives::Dimension const &d);
        virtual primitives::Dimension getSize () const;

        virtual bool isFill () const;
        virtual void setFill (bool value);

        virtual float getStrokeWidth () const;
        virtual void setStrokeWidth (float value);

        virtual float getStrokeDash () const;
        virtual void setStrokeDash (float value);

        virtual primitives::Color getStrokeColor () const;
        virtual void setStrokeColor (const primitives::Color &value);

        virtual primitives::Color getFillColor () const;
        virtual void setFillColor (const primitives::Color &value);

        virtual primitives::Box getBoundingBox () const;
        virtual bool isContainter () const { return false; }

        /// For converting coordinates to common space. Works after container has done its job.
        virtual primitives::Point convertToScaleLayer (primitives::Point const &p) const;

        /// Stores this into self as g_object value.
        virtual void setCppImplementation ();

        IDrawingEventHandler *getEventHandler () const { return eventHandler; }
        void setEventHandler (IDrawingEventHandler *value) { eventHandler = value; }

        virtual Core::StringVector getPropertyViews () const __tiliae_no_reflect__;
        void setPropertyView (const std::string &value) { propertyView = value; }

        IRoutable *getRoutable () { return routable; }
        void setRoutable (IRoutable *r) { routable = r; }

        void contId (std::string const &i) { id = i; }
        std::string getId () const { return id; }

        void setSizeConstraint (ISizeConstraint *s) { sizeConstraint = s; }
        ISizeConstraint const *getSizeConstraint () const { return sizeConstraint; }

        /*---------------------------------------------------------------------------*/

        virtual bool isConnectSignals () __tiliae_no_reflect__ { return false; }
        virtual bool onButtonPress (Event const &e) __tiliae_no_reflect__ { return false; }
        virtual bool onButtonRelease (Event const &e) __tiliae_no_reflect__ { return false; }
        virtual bool onMotion (Event const &e) __tiliae_no_reflect__ { return false; }
        virtual bool onEnter (Event const &e) __tiliae_no_reflect__ { return false; }
        virtual bool onLeave (Event const &e) __tiliae_no_reflect__ { return false; }
        virtual bool onScroll (Event const &e) __tiliae_no_reflect__ { return false; }
        virtual bool onKeyPress (Event const &e) __tiliae_no_reflect__ { return false; }

        /*---------------------------------------------------------------------------*/

        virtual void onReroute (Avoid::ConnRef *) __tiliae_no_reflect__ {}

protected:
        friend void abstractActorOnFinalize (void *ptr);
        void onFinalize () { clutterDestroyed = true; }

        ClutterActor *self = nullptr;

private:
        friend gboolean on_actor_motion (ClutterActor *stage, ClutterEvent *ev, gpointer data);
        friend gboolean on_actor_button_press (ClutterActor *actor, ClutterEvent *ev, gpointer data);

        IClutterActor *parent = nullptr;
        IDrawingEventHandler *eventHandler = nullptr;
        bool selectable = true;
        bool clutterDestroyed = false;
        std::string propertyView;
        std::string id;
        primitives::Point stagePrev;
        primitives::Point parentPrev;
        IRoutable *routable = nullptr;
        ISizeConstraint *sizeConstraint = nullptr;
};

#endif // ABSTRACTACTOR_H
