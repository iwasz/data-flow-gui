/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONNECTABLE_H
#define ICONNECTABLE_H

#include "Anchor.h"
#include <ReflectionParserAnnotation.h>

/**
 * Every (drawable) object which IConnector can connect to.
 */
struct __tiliae_reflect__ IConnectable {
        virtual ~IConnectable () {}

//        virtual AnchorVector &getAnchors () = 0;
//        virtual AnchorVector const &getAnchors () const = 0;
//        virtual void addAnchor (std::unique_ptr <Anchor> anchor) = 0;
        virtual Anchor *getAnchor (size_t i) __tiliae_no_reflect__ = 0;
        virtual Anchor const *getAnchor (size_t i) const __tiliae_no_reflect__ = 0;
};

#endif // ICONNECTABLE_H
