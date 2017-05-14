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
        RoutableRoot ();
        virtual ~RoutableRoot () {}

        Avoid::Router *getRouter () __tiliae_no_reflect__ { return &router; }
        bool processTransaction () { return router.processTransaction (); }
        virtual void setRouter (Avoid::Router *r) __tiliae_no_reflect__ {}
        void outputInstanceToSVG (std::string const &s) { router.outputInstanceToSVG (s); }

private:
        Avoid::Router router;
};

#endif // ROUTABLEROOT_H
