/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DF_GRAPHIC_NODE_H
#define DF_GRAPHIC_NODE_H

#include <INode.h>
#include "IDFNode.h"

class __tiliae_reflect__ DFNode : public IDFNode {
public:
        virtual ~DFNode () {}

private:

        flow::INode *node;
//        I
};


#endif // NODE_H
