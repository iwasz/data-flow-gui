/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CIRCULARNODE_H
#define CIRCULARNODE_H

#include "AbstractActor.h"
#include "AbstractNodeView.h"
#include "primitives/Geometry.h"

/**
 * This is only a view.
 */
class __tiliae_reflect__ CircularNode : public AbstractActor, public AbstractNodeView {
public:
        CircularNode ();
        virtual ~CircularNode () {}
        void init ();

        bool isFill () const;
        void setFill (bool value);

        float getStrokeWidth () const;
        void setStrokeWidth (float value);

        float getStrokeDash () const;
        void setStrokeDash (float value);

        primitives::Color getStrokeColor () const;
        void setStrokeColor (const primitives::Color &value);

        primitives::Color getFillColor () const;
        void setFillColor (const primitives::Color &value);

        virtual std::string getText () const;
        virtual void setText (std::string const t);

        virtual std::string getFont () const;
        virtual void setFont (std::string const t);

        virtual primitives::Color getFontColor () const;
        virtual void setFontColor (const primitives::Color &value);

        virtual bool isTextEditable () const;
        virtual void setTextEditable (bool b);

        virtual void onAllocate (primitives::Box const &b);
        virtual primitives::Point getPortPosition (int i) const;

        virtual void visit (IDataFile *d) { d->onCircularNode (this); }
};

#endif // CIRCULARNODE_H
