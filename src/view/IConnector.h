/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include <ReflectionParserAnnotation.h>

class Anchor;

/**
 * Straight or bent line (whatever, impl. will define), directed or not (whetever, impl. will define),
 * which connects one IConnectable to another. In other words visual representation is implementation
 * dependant, but IConnector itself is internally directed i.e. it has two ends : a and b.
 */
struct __tiliae_reflect__ IConnector {
        enum Side { A, B };
        virtual ~IConnector () {}

        virtual void connect (Anchor *a, Side s) = 0;

        virtual void disconnect (Side s) = 0;

        // Event handlers

        virtual void onMoveAnchor (float x, float y, Side s) = 0;
};

#endif // ICONNECTOR_H
