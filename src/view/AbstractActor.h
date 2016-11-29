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

protected:

        ClutterActor *self = 0;
};

#endif // ABSTRACTACTOR_H
