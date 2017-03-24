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

class __tiliae_reflect__ Rectangle : public AbstractActor {
public:
        Rectangle ();
        virtual ~Rectangle () {}

        virtual std::string visit (IDataFile *d, IDataFile::Operation o) { return d->onConnector (this, o); }
};

#endif // RECTANGLE_H
