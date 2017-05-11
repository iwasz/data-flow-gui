/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONNECTORROUTABLE_H
#define CONNECTORROUTABLE_H

#include "AbstractRoutable.h"

class __tiliae_reflect__ ConnectorRoutable : public AbstractRoutable {
public:
        virtual ~ConnectorRoutable () {}
        virtual void init (primitives::Point const &p, primitives::Dimension const &d, IRoutableObserver *o = nullptr) __tiliae_no_reflect__;
        void connect (RoutablePin *pin, Side s) __tiliae_no_reflect__;

private:
        static void onRerouteCallback (void *v);

private:
        Avoid::ConnRef *connRef = nullptr;
};

#endif // CONNECTORROUTABLE_H
