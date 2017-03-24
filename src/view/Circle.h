/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_CIRCLE_H
#define DATA_FLOW_CIRCLE_H

#include "AbstractActor.h"
#include "Stage.h"
#include <ReflectionParserAnnotation.h>
#include <clutter/clutter.h>
#include <string>

class __tiliae_reflect__ Circle : public AbstractActor {
public:
        Circle ();
        virtual ~Circle () {}
        virtual std::string visit (IDataFile *d, IDataFile::Operation o) { return d->onCircle (this, o); }
};

#endif // CIRCLE_H
