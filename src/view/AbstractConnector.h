/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTCONNECTOR_H
#define ABSTRACTCONNECTOR_H

#include "IConnector.h"
#include "Port.h"
#include "primitives/Direction.h"
#include <libavoid.h>

/**
 * @brief The AbstractConnector class
 */
class __tiliae_reflect__ AbstractConnector : public IConnector {
public:
        virtual ~AbstractConnector () {}

        virtual void connect (Port *an, Side s);
        virtual void disconnect ();

        Port *getPort (Side s) __tiliae_no_reflect__ { return (Side::A) ? (a) : (b); }
        Port const *getPort (Side s) const __tiliae_no_reflect__ { return (Side::A) ? (a) : (b); }

private:
        static void onRerouteCallback (void *v);
        Avoid::ConnRef *connRef = nullptr;
        Port *a = nullptr;
        Port *b = nullptr;
};

#endif // ABSTRACTCONNECTOR_H
