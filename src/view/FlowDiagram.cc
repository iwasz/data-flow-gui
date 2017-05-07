/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "FlowDiagram.h"
#include <libavoid/libavoid.h>

/*****************************************************************************/

struct FlowDiagram::Impl {

        Avoid::Router router{ Avoid::OrthogonalRouting };
};

/*****************************************************************************/

FlowDiagram::FlowDiagram () { impl = new Impl; }

/*****************************************************************************/

FlowDiagram::~FlowDiagram () { delete impl; }
