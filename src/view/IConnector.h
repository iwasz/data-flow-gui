/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "Anchor.h"

/**
 * Straight or bent line (whatever, impl. will define), directed or not (whetever, impl. will define),
 * which connects one IConnectable to another. In other words visual representation is implementation
 * dependant, but IConnector itself is internally directed i.e. it has two ends : a and b.
 */
struct IConnector {
        virtual ~IConnector () {}

        virtual void connectA (Anchor *a) = 0;
        virtual void connectB (Anchor *a) = 0;

        virtual void disconnectA () = 0;
        virtual void disconnectB () = 0;

        // Event handlers

        virtual void onMoveAnchorA (float x, float y) = 0;
        virtual void onMoveAnchorB (float x, float y) = 0;
};

#endif // ICONNECTOR_H
