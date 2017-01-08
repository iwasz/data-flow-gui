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

class __tiliae_reflect__ Stage : public AbstractActor {
public:

        Stage ();
        virtual ~Stage () {}

        GtkWidget *getClutterWidget () { return clutterWidget; }
        void setParent (IClutterActor *parent) { throw Core::Exception ("Not implemented"); }

        virtual Color getFillColor () const;
        virtual void setFillColor (const Color &value);

private:
        GtkWidget *clutterWidget;
};

#endif // STAGE_H
