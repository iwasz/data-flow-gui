/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ROUTABLEROOT_H
#define ROUTABLEROOT_H

#include "AbstractRoutable.h"

class __tiliae_reflect__ RoutableRoot : public AbstractRoutable {
public:
        virtual ~RoutableRoot () {}
        Avoid::Router *getRouter () __tiliae_no_reflect__ { return &router; }
        bool processTransaction () { return router.processTransaction (); }
        virtual void setRouter (Avoid::Router *r) __tiliae_no_reflect__ {}

private:
        Avoid::Router router{ Avoid::PolyLineRouting };
};

#endif // ROUTABLEROOT_H
