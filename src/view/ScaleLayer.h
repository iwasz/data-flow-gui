/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCALELAYER_H
#define SCALELAYER_H

#include "AbstractActor.h"
#include <ReflectionParserAnnotation.h>
#include <clutter-gtk/clutter-gtk.h>
#include <string>

#define SCALE_SURFACE_SIZE 10000

class __tiliae_reflect__ ScaleLayer : public AbstractActor {
public:
        ScaleLayer ();
        virtual ~ScaleLayer ();

        /// Warning, warning! It returns somethig only after container created the instance.
        static ScaleLayer *singleton () { return instance; }

        virtual bool isContainter () const { return true; }
        virtual bool isSelectable () const { return false; }
        void zoomIn (primitives::Point const &center = primitives::Point ());
        void zoomOut (primitives::Point const &center = primitives::Point ());
        void zoom (double f);
        void pan (primitives::Point const &n);

        virtual bool isFill () const { throw Core::Exception ("Not implemented"); }
        virtual void setFill (bool value) { throw Core::Exception ("Not implemented"); }

        virtual float getStrokeWidth () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeWidth (float value) { throw Core::Exception ("Not implemented"); }

        virtual float getStrokeDash () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeDash (float value) { throw Core::Exception ("Not implemented"); }

        virtual primitives::Color getStrokeColor () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeColor (const primitives::Color &value) { throw Core::Exception ("Not implemented"); }

        virtual primitives::Color getFillColor () const { throw Core::Exception ("Not implemented"); }
        virtual void setFillColor (const primitives::Color &value) { throw Core::Exception ("Not implemented"); }

        virtual void visit (IDataFileSave *) {}

private:

        void scale (primitives::Point const &center, float scale);


        friend class Stage;
        static ScaleLayer *instance;

        struct Impl;
        Impl *impl;
};

#endif // SCALELAYER_H
