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

        virtual std::shared_ptr<flow::INode> getNode () { return node; }
        virtual void setNode (std::shared_ptr<flow::INode> n);

private:
        std::shared_ptr<flow::INode> node;
};

#endif // ABSTRACTNODEVIEW_H
