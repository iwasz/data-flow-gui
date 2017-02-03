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
#include "gui/drawing/IDrawingEventHandler.h"
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

        virtual void setPosition (Point const &p);
        virtual Point getPosition () const;

        virtual void setSize (Dimension const &d);
        virtual Dimension getDimension () const;

        virtual bool isFill () const;
        virtual void setFill (bool value);

        virtual float getStrokeWidth () const;
        virtual void setStrokeWidth (float value);

        virtual float getStrokeDash () const;
        virtual void setStrokeDash (float value);

        virtual Color getStrokeColor () const;
        virtual void setStrokeColor (const Color &value);

        virtual Color getFillColor () const;
        virtual void setFillColor (const Color &value);

        virtual Box getBoundingBox () const;
        virtual bool isContainter () const { return false; }

        /// For converting coordinates to common space. Works after container has done its job.
        virtual Point convertToScaleLayer (Point const &p) const;

        /// Stores this into self as g_object value.
        virtual void setCppImplementation ();

        IDrawingEventHandler *getEventHandler () const { return eventHandler; }
        void setEventHandler (IDrawingEventHandler *value) { eventHandler = value; }

        /*---------------------------------------------------------------------------*/

        virtual bool isConnectSignals () { return false; }
        virtual bool onButtonPress (Event const &e) { return false; }
        virtual bool onButtonRelease (Event const &e) { return false; }
        virtual bool onMotion (Event const &e) { return false; }
        virtual bool onEnter (Event const &e) { return false; }
        virtual bool onLeave (Event const &e) { return false; }
        virtual bool onScroll (Event const &e) { return false; }
        virtual bool onKeyPress (Event const &e) { return false; }

        // TODO private
        Point stagePrev;
        Point parentPrev;

protected:
        friend void abstractActorOnFinalize (void *ptr);
        void onFinalize () { clutterDestroyed = true; }

        ClutterActor *self = 0;

private:
        IDrawingEventHandler *eventHandler = nullptr;
        bool selectable = true;
        bool clutterDestroyed = false;
};

#endif // ABSTRACTACTOR_H
