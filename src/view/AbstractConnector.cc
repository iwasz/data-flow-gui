/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractConnector.h"

/*****************************************************************************/

void AbstractConnector::connect (Anchor *an, Side s)
{
        an->connect (this, s);
        if (s == A) {
                a = an;
                setAFacing (a->getFacing ());
        }
        else {
                b = an;
                setBFacing (b->getFacing ());
        }

        onConnectAnchor (an->getPosition (), s);
}

/*****************************************************************************/

void AbstractConnector::disconnect (/*Side s*/)
{
        //        a->disconnect (this, A);
        //        if (s == A) {
        //                a = nullptr;
        //        }
        //                onDisconnectAnchor (a->getPosition (), s);
        //        else {
        //                b = nullptr;
        //                onDisconnectAnchor (b->getPosition (), s);
        //        }

        setAFacing (NONE);
        setBFacing (NONE);
        a->disconnect (this);
        b->disconnect (this);
        a = nullptr;
        b = nullptr;
        onDisconnectAnchor (/*a->getPosition (), s*/);
}
