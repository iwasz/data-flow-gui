/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VISIBLE_PORT_H
#define VISIBLE_PORT_H

#include "Anchor.h"
#include "primitives/Color.h"
#include <ReflectionParserAnnotation.h>
#include <vector>

/**
 * This is only a view. Represents a port (place on a node you can connect a connector to).
 */
class __tiliae_reflect__ Port : public Core::Object {
public:
        float angle;
        float size;
        Color color;
        Anchor anchor;
};

/**
 * Collection of ports.
 */
typedef __tiliae_reflect__ std::vector<Port> PortVector;

#endif // PORT_H
