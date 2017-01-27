/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTACTOR_H
#define ABSTRACTACTOR_H

#include "IClutterActor.h"
#include <core/Exception.h>

extern "C" void abstractActorOnFinalize (void *ptr);

class __tiliae_reflect__ AbstractActor : public IClutterActor {
public:
        virtual ~AbstractActor ();

        virtual void setParent (IClutterActor *parent);
        virtual ClutterActor *getActor () { return self; }

        virtual bool isVisible () const;
        virtual void setVisible (bool value);

        virtual bool isSelectable () const { return selectable; }
        virtual void setSelectable (bool value) { selectable = value; }

        virtual bool isReactive () const;
        virtual void setReactive (bool value);

        virtual void setPosition (Point const &p);
        virtual Point getPosition () const;

        virtual void setSize (Dimension const &d);
        virtual Dimension getDimension () const;

        virtual bool isFill () const;
        virtual void setFill (bool value);

        virtual float getStrokeWidth () const;
        virtual void setStrokeWidth (float value);

        virtual float getStrokeDash () const;
        virtual void setStrokeDash (float value);

        virtual Color getStrokeColor () const;
        virtual void setStrokeColor (const Color &value);

        virtual Color getFillColor () const;
        virtual void setFillColor (const Color &value);

        virtual Box getBoundingBox () const;
        virtual bool isContainter () const { return false; }

        /// For converting coordinates to common space. Works after container has done its job.
        virtual Point convertToScaleLayer (Point const &p) const;

        /// Stores this into self as g_object value.
        virtual void setCppImplementation ();

protected:
        friend void abstractActorOnFinalize (void *ptr);
        void onFinalize () { clutterDestroyed = true; }

        ClutterActor *self = 0;
        bool selectable = true;
        bool clutterDestroyed = false;
};

#endif // ABSTRACTACTOR_H
