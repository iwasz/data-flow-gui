/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATAFLOW_GUI_STUFF_BUTTON_H
#define DATAFLOW_GUI_STUFF_BUTTON_H

#include "AbstractActor.h"
#include "AbstractNodeView.h"
#include "primitives/Geometry.h"
#include <string>

class __tiliae_reflect__ Button : public AbstractActor, public AbstractNodeView {
public:
        Button ();
        virtual ~Button ();
        void init ();

        /*---------------------------------------------------------------------------*/

        std::string getText () const;
        void setText (std::string const t);

        std::string getFont () const;
        void setFont (std::string const t);

        primitives::Color getFontColor () const;
        void setFontColor (const primitives::Color &value);

        /*---------------------------------------------------------------------------*/

        virtual void setNode (std::shared_ptr<flow::INode> n);
        virtual void onAllocate (primitives::Box const &b);
        virtual void onPress ();
        virtual void onRelease ();
        virtual primitives::Point getPortPosition (int i) const;

        virtual void visit (IDataFileSave *d) { d->onButton (this); }

private:
        struct Impl;
        Impl *impl;
};

#endif // BUTTON_H
