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

#define SCALE_SURFACE_WIDTH 10000
#define SCALE_SURFACE_HEIGHT 10000

class __tiliae_reflect__ ScaleLayer : public AbstractActor {
public:
        ScaleLayer ();
        virtual ~ScaleLayer () {}

        virtual bool isContainter () const { return true; }
        void zoomIn ();
        void zoomOut ();
        void zoom (double f);

};

#endif // SCALELAYER_H
