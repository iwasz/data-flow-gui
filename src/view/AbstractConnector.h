/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTCONNECTOR_H
#define ABSTRACTCONNECTOR_H

#include "Anchor.h"
#include "IConnector.h"
#include "primitives/Direction.h"

/**
 * @brief The AbstractConnector class
 */
class __tiliae_reflect__ AbstractConnector : public IConnector {
public:
        virtual ~AbstractConnector () {}

        virtual void connect (Anchor *an, Side s);
        virtual void disconnect (/*Side s*/);

        virtual Direction getAFacing () const = 0;
        virtual Direction getBFacing () const = 0;

        virtual void setAFacing (Direction value) = 0;
        virtual void setBFacing (Direction value) = 0;

        Anchor *getAnchorA () { return a; } /// For load-save
        Anchor *getAnchorB () { return b; } /// For load-save

private:
        /// Anchor at the start of the connector
        Anchor *a = nullptr;
        /// Anchor at the start of the connector
        Anchor *b = nullptr;
};

#endif // ABSTRACTCONNECTOR_H
