/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DFF_STAgE_FLOWDIAGRAM_H
#define DFF_STAgE_FLOWDIAGRAM_H

#include "Stage.h"

class __tiliae_reflect__ FlowDiagram : public Stage {
public:

        FlowDiagram ();
        virtual ~FlowDiagram ();

private:

        struct Impl;
        Impl *impl;
};

#endif // FLOWDIAGRAM_H
