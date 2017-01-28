/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DF_FLOW_INODEVIEW_FOR_LIFE_H
#define DF_FLOW_INODEVIEW_FOR_LIFE_H

#include "Port.h"
#include <ReflectionParserAnnotation.h>
#include <core/INode.h>
#include <core/Object.h>
#include <memory>

/**
 * Representing a visual container for a flow::INode.
 */
struct __tiliae_reflect__ INodeView : public virtual Core::Object {
        virtual ~INodeView () {}

        virtual std::shared_ptr<flow::INode> getNode () = 0;
        virtual void setNode (std::shared_ptr<flow::INode> n) = 0;

        virtual Anchor *getAnchor (size_t i) __tiliae_no_reflect__ = 0;
        virtual Anchor const *getAnchor (size_t i) const __tiliae_no_reflect__ = 0;

        virtual PortVector &getPorts () = 0;
        virtual Point getPortPosition (int i) const = 0;
};

#endif // INODEVIEW_H
