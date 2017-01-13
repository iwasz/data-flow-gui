/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTACTOR_H
#define ABSTRACTACTOR_H

#include <core/Exception.h>
#include "IClutterActor.h"
#include "abstractActor.h"

class __tiliae_reflect__ AbstractActor : public IClutterActor {
public:
        virtual ~AbstractActor () {}

        virtual void setParent (IClutterActor *parent);
        virtual ClutterActor *getActor () { return self; }

        virtual bool getVisible () const;
        virtual void setVisible (bool value);

        virtual void setPosition (Point const &p);
        virtual Point getPosition () const;

        virtual void setSize (Dimension const &d);
        virtual Dimension getDimension () const;

        virtual bool isFill () const { throw Core::Exception ("Not implemented"); }
        virtual void setFill (bool value) { throw Core::Exception ("Not implemented"); }

        virtual float getStrokeWidth () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeWidth (float value) { throw Core::Exception ("Not implemented"); }

        virtual float getStrokeDash () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeDash (float value) { throw Core::Exception ("Not implemented"); }

        virtual Color getStrokeColor () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeColor (const Color &value) { throw Core::Exception ("Not implemented"); }

        virtual Color getFillColor () const { throw Core::Exception ("Not implemented"); }
        virtual void setFillColor (const Color &value) { throw Core::Exception ("Not implemented"); }

        /// Stores this into self as g_object value.
        virtual void setCppImplementation ();

protected:

        ClutterActor *self = 0;
};

#endif // ABSTRACTACTOR_H
