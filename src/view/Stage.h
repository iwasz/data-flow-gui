/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLUTTER_DATA_FLOW_STAGE_H
#define CLUTTER_DATA_FLOW_STAGE_H

#include "AbstractActor.h"
#include <ReflectionParserAnnotation.h>
#include <clutter-gtk/clutter-gtk.h>
#include <string>

class ScaleLayer;

class __tiliae_reflect__ Stage : public AbstractActor {
public:
        Stage ();
        virtual ~Stage () {}

        GtkWidget *getClutterWidget () { return clutterWidget; }
        void setParent (IClutterActor *parent) { throw Core::Exception ("Not implemented"); }

        virtual bool isFill () const { throw Core::Exception ("Not implemented"); }
        virtual void setFill (bool value) { throw Core::Exception ("Not implemented"); }

        virtual float getStrokeWidth () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeWidth (float value) { throw Core::Exception ("Not implemented"); }

        virtual float getStrokeDash () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeDash (float value) { throw Core::Exception ("Not implemented"); }

        virtual Color getStrokeColor () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeColor (const Color &value) { throw Core::Exception ("Not implemented"); }

        virtual Color getFillColor () const;
        virtual void setFillColor (const Color &value);

        virtual bool isSelectable () const { return false; }

        ScaleLayer *getScaleLayer () const { return scaleLayer; }
        void setScaleLayer (ScaleLayer *layer);

        /*---------------------------------------------------------------------------*/

        virtual bool isConnectSignals () { return true; }
        virtual bool onButtonPress (Event const &e);
        virtual bool onButtonRelease (Event const &e);
        virtual bool onMotion (Event const &e);
        virtual bool onScroll (Event const &e);
        virtual bool onKeyPress (Event const &e);

        virtual void visit (IDataFile *) {}

private:
        GtkWidget *clutterWidget;
        ScaleLayer *scaleLayer;
};

#endif // STAGE_H
