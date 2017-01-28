/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTNODEVIEW_H
#define ABSTRACTNODEVIEW_H

#include "INodeView.h"

class __tiliae_reflect__ AbstractNodeView : public INodeView {
public:
        virtual ~AbstractNodeView () {}

        void glueInit ();

        virtual std::shared_ptr<flow::INode> getNode () { return node; }
        virtual void setNode (std::shared_ptr<flow::INode> n) { node = n; }

        virtual Anchor *getAnchor (size_t i) __tiliae_no_reflect__;
        virtual Anchor const *getAnchor (size_t i) const __tiliae_no_reflect__;

        virtual PortVector &getPorts () { return ports; }

private:
        std::shared_ptr<flow::INode> node;
        PortVector ports;
};

#endif // ABSTRACTNODEVIEW_H
