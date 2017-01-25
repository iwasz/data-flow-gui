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
#include "Anchor.h"

/**
 * @brief The AbstractConnector class
 */
class __tiliae_reflect__  AbstractConnector : public IConnector {
public:
        virtual ~AbstractConnector () {}

        virtual void connect (Anchor *an, Side s);
        virtual void disconnect (/*Side s*/);

private:

        Anchor *a = nullptr;
        Anchor *b = nullptr;
};

#endif // ABSTRACTCONNECTOR_H
