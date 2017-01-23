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

#define SCALE_SURFACE_WIDTH 10000
#define SCALE_SURFACE_HEIGHT 10000

class __tiliae_reflect__ Stage : public AbstractActor {
public:
        Stage ();
        virtual ~Stage () {}

        GtkWidget *getClutterWidget () { return clutterWidget; }
        void setParent (IClutterActor *parent) { throw Core::Exception ("Not implemented"); }
        virtual ClutterActor *getActor () { return scale; }

        virtual Color getFillColor () const;
        virtual void setFillColor (const Color &value);

        void zoomIn ();
        void zoomOut ();
        void zoom (double f);

private:
        GtkWidget *clutterWidget;
        ClutterActor *scale;
};

#endif // STAGE_H
