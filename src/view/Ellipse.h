/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_ELLIPSE_H
#define DATA_FLOW_ELLIPSE_H

#include "AbstractActor.h"
#include <ReflectionParserAnnotation.h>

class __tiliae_reflect__ Ellipse : public AbstractActor {
public:
        Ellipse ();
        virtual ~Ellipse () {}
        virtual void visit (IDataFileSave *d) { /*d->onCircle (this);*/}
};

#endif // CIRCLE_H
