/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_SIMPLEDISPLAY_H
#define DATA_FLOW_SIMPLEDISPLAY_H

#include "AbstractActor.h"
#include <ReflectionParserAnnotation.h>

class __tiliae_reflect__ SimpleDisplay : public AbstractActor {
public:
        SimpleDisplay ();
        virtual ~SimpleDisplay () {}
        virtual void visit (IDataFileSave *d) { /*d->onCircle (this);*/}
};

#endif // CIRCLE_H
