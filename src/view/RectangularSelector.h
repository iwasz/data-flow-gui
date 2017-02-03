/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_RECTANGULAR_SELECTOR_H
#define DATA_FLOW_RECTANGULAR_SELECTOR_H

#include "Rectangle.h"
#include <ReflectionParserAnnotation.h>
#include <clutter/clutter.h>
#include <string>

class __tiliae_reflect__ RectangularSelector : public Rectangle {
public:
        RectangularSelector ();
        virtual ~RectangularSelector () {}

//        virtual bool isConnectSignals () { return true; }
        virtual bool onButtonPress (Event const &e);
        virtual bool onButtonRelease (Event const &e);
        virtual bool onMotion (Event const &e);
};

#endif // RECTANGLE_H
