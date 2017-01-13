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
        }
        else {
                b = an;
        }
}

/*****************************************************************************/

void AbstractConnector::disconnect (Side s)
{
        a->disconnect (this, A);
        if (s == A) {
                a = nullptr;
        }
        else {
                b = nullptr;
        }
}