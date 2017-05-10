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
#include "gui/main/IDrawingEventHandler.h"
#include <core/Exception.h>

extern "C" void abstractActorOnFinalize (void *ptr);

/**
 * @brief The AbstractActor class
 */
class __tiliae_reflect__ AbstractActor : public IClutterActor {
public:
        void init ();
        virtual ~AbstractActor ();

        virtual void setParent (IClutterActor *parent);
        virtual ClutterActor *getActor () { return self; }

        virtual bool isVisible () const;
        virtual void setVisible (bool value);

        virtual bool isSelectable () const { return selectable; }
        virtual void setSelectable (bool value) { selectable = value; }

        virtual bool isReactive () const;
        virtual void setReactive (bool value);

        bool isRouting () const { return routing; }
        void setRouting (bool value) { routing = value; }

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

        virtual Avoid::Router *getRouter () __tiliae_no_reflect__ { return router; }
        virtual Avoid::ShapeRef *getShapeRef () __tiliae_no_reflect__ { return shapeRef; }

        /*---------------------------------------------------------------------------*/

        virtual bool isConnectSignals () { return false; }
        virtual bool onButtonPress (Event const &e) { return false; }
        virtual bool onButtonRelease (Event const &e) { return false; }
        virtual bool onMotion (Event const &e) { return false; }
        virtual bool onEnter (Event const &e) { return false; }
        virtual bool onLeave (Event const &e) { return false; }
        virtual bool onScroll (Event const &e) { return false; }
        virtual bool onKeyPress (Event const &e) { return false; }

        void contId (std::string const &i) { id = i; }
        std::string getId () const { return id; }

        // TODO private
        primitives::Point stagePrev;
        primitives::Point parentPrev;

protected:
        friend void abstractActorOnFinalize (void *ptr);
        void onFinalize () { clutterDestroyed = true; }
        void setRouter (Avoid::Router *r) { router = r; }

        ClutterActor *self = nullptr;

private:
        IDrawingEventHandler *eventHandler = nullptr;
        bool selectable = true;
        bool clutterDestroyed = false;
        bool routing = false;
        std::string propertyView;
        std::string id;
        Avoid::Router *router = nullptr;
        Avoid::ShapeRef *shapeRef = nullptr;
};

#endif // ABSTRACTACTOR_H
