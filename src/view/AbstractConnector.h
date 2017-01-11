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
class AbstractConnector : public IConnector {
public:
        virtual ~AbstractConnector () {}

        virtual void connectA (Anchor *an) { an->connect (this, Anchor::A); a = an; }
        virtual void connectB (Anchor *an) { an->connect (this, Anchor::B); b = an; }

        virtual void disconnectA () { a->disconnect (this, Anchor::A); a = nullptr; }
        virtual void disconnectB () { b->disconnect (this, Anchor::B); b = nullptr; }

private:

        Anchor *a = nullptr;
        Anchor *b = nullptr;
};

#endif // ABSTRACTCONNECTOR_H
