/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_RECTANGLE_H
#define DATA_FLOW_RECTANGLE_H

#include "AbstractActor.h"
#include "Stage.h"
#include <ReflectionParserAnnotation.h>
#include <clutter/clutter.h>
#include <string>

class __tiliae_reflect__ Rect : public AbstractActor {
public:
        Rect ();
        virtual ~Rect () {}

        virtual void visit (IDataFileSave *d) { d->onConnector (this); }
};

#endif // RECTANGLE_H
