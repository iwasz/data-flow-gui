/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "primitives/Geometry.h"
#include <ReflectionParserAnnotation.h>
// TODO Remove
#include <libavoid.h>

class Port;

/**
 * Straight or bent line (whatever, impl. will define), directed or not (whetever, impl. will define),
 * which connects one IConnectable to another. In other words visual representation is implementation
 * dependant, but IConnector itself is internally directed i.e. it has two ends : a and b.
 */
//struct __tiliae_reflect__ IConnector {
//        enum Side { A, B };
//        virtual ~IConnector () {}

//        virtual void connect (Port *a, Side s) = 0;
//        virtual void disconnect (/*Side s*/) = 0;

//        // Event handlers

//        //        virtual void onConnectAnchor (primitives::Point const &p, Side s) = 0;
//        //        virtual void onMoveAnchor (primitives::Point const &p, Side s) = 0;
//        //        virtual void onDisconnectAnchor (/*Side s*/) = 0;

//        /// TODO change API from conRef to some primitives::polygon
//        virtual void onReroute (Avoid::ConnRef *) = 0;
//};

#endif // ICONNECTOR_H
