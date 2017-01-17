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
        std::shared_ptr<flow::INode> getNode () { return std::move (node); }
        void setNode (std::shared_ptr<flow::INode> n) { node = std::move (n); }

private:
        std::shared_ptr<flow::INode> node;
};

#endif // ABSTRACTNODEVIEW_H
