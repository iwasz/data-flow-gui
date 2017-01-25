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
        virtual ~ScaleLayer () {}

        /// Warning, warning! It returns somethig only after container created the instance.
        static ScaleLayer *singleton () { return instance; }

        virtual bool isContainter () const { return true; }
        virtual bool isSelectable () const { return false; }
        void zoomIn (Point const &center = Point ());
        void zoomOut (Point const &center = Point ());
        void zoom (double f);
        void pan (Point const &n);

private:
        friend class Stage;
        static ScaleLayer *instance;
};

#endif // SCALELAYER_H
