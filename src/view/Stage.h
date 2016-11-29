/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLUTTER_DATA_FLOW_STAGE_H
#define CLUTTER_DATA_FLOW_STAGE_H

#include <ReflectionParserAnnotation.h>
#include <clutter-gtk/clutter-gtk.h>
#include <string>
#include "IClutterActor.h"

class __tiliae_reflect__ Stage : public IClutterActor {
public:

        virtual ~Stage () {}
        void init ();

        GtkWidget *getClutterWidget () { return clutterWidget; }
        ClutterActor *getActor () { return stage; }

        std::string getColor () const { return color; }
        void setColor (const std::string &value) { color = value; }

private:
        std::string color;
        GtkWidget *clutterWidget;
        ClutterActor *stage;
};

#endif // STAGE_H
