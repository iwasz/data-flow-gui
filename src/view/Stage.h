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
#include <core/Exception.h>
#include <string>

class __tiliae_reflect__ Stage : public AbstractActor {
public:
        virtual ~Stage () {}
        void init ();

        GtkWidget *getClutterWidget () { return clutterWidget; }
        void setParent (IClutterActor *parent) { throw Core::Exception ("Not implemented"); }

        bool isFill () const { throw Core::Exception ("Not implemented"); }
        void setFill (bool value) { throw Core::Exception ("Not implemented"); }

        float getStrokeWidth () const { throw Core::Exception ("Not implemented"); }
        void setStrokeWidth (float value) { throw Core::Exception ("Not implemented"); }

        float getStrokeDash () const { throw Core::Exception ("Not implemented"); }
        void setStrokeDash (float value) { throw Core::Exception ("Not implemented"); }

        std::string getStrokeColor () const { throw Core::Exception ("Not implemented"); }
        void setStrokeColor (const std::string &value) { throw Core::Exception ("Not implemented"); }

        virtual std::string getFillColor () const;
        virtual void setFillColor (const std::string &value);

private:
//        std::string color;
        GtkWidget *clutterWidget;
};

#endif // STAGE_H
