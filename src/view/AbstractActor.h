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

        virtual std::string getStrokeColor () const { throw Core::Exception ("Not implemented"); }
        virtual void setStrokeColor (const std::string &value) { throw Core::Exception ("Not implemented"); }

        virtual std::string getFillColor () const { throw Core::Exception ("Not implemented"); }
        virtual void setFillColor (const std::string &value) { throw Core::Exception ("Not implemented"); }

protected:

        ClutterActor *self = 0;
};

#endif // ABSTRACTACTOR_H
