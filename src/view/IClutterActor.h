/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLUTTER_ICONTAINER_H
#define CLUTTER_ICONTAINER_H

#include "gui/main/IDrawingEventHandler.h"
#include "gui/saveLoadFile/IDataFileSave.h"
#include "primitives/Color.h"
#include "primitives/Geometry.h"
#include "routable/IRoutable.h"
#include <ReflectionParserAnnotation.h>
#include <clutter-gtk/clutter-gtk.h>
#include <core/Object.h>
#include <core/Typedefs.h>
#include <memory>
#include <set>
#include <string>

/**
 * Interface for views.
 */
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

        virtual void setPosition (primitives::Point const &p) = 0;
        virtual void move (primitives::Dimension const &d) = 0;
        virtual primitives::Point getPosition () const = 0;
        virtual primitives::Point getScaleLayerPosition () const = 0;

        virtual void setSize (primitives::Dimension const &d) = 0;
        virtual primitives::Dimension getSize () const = 0;

        virtual bool isFill () const = 0;
        virtual void setFill (bool value) = 0;

        virtual float getStrokeWidth () const = 0;
        virtual void setStrokeWidth (float value) = 0;

        virtual float getStrokeDash () const = 0;
        virtual void setStrokeDash (float value) = 0;

        virtual primitives::Color getStrokeColor () const = 0;
        virtual void setStrokeColor (const primitives::Color &value) = 0;

        virtual primitives::Color getFillColor () const = 0;
        virtual void setFillColor (const primitives::Color &value) = 0;

        virtual bool isContainter () const = 0;

        virtual primitives::Box getBoundingBox () const = 0;
        virtual primitives::Point convertToScaleLayer (primitives::Point const &p) const = 0;

        virtual Core::StringVector getPropertyViews () const = 0;

        /// Save/load files
        virtual void visit (IDataFileSave *) = 0;
        virtual std::string getId () const = 0;

        virtual IRoutable *getRoutable () = 0;

        /*---------------------------------------------------------------------------*/

        virtual bool isConnectSignals () = 0;
        virtual bool onButtonPress (Event const &e) = 0;
        virtual bool onButtonRelease (Event const &e) = 0;
        virtual bool onMotion (Event const &e) = 0;
        virtual bool onEnter (Event const &e) = 0;
        virtual bool onLeave (Event const &e) = 0;
        virtual bool onScroll (Event const &e) = 0;
        virtual bool onKeyPress (Event const &e) = 0;
};

typedef __tiliae_reflect__ std::vector<IClutterActor *> ClutterActorVector;
typedef std::set<IClutterActor *> ClutterActorSet;

#endif // ICONTAINER_H
