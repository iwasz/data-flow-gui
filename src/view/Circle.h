/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_CIRCLE_H
#define DATA_FLOW_CIRCLE_H

#include <Tiliae.h>
#include <clutter/clutter.h>

class __tiliae_reflect__ Circle {
public:

        Circle ();
        virtual ~Circle ();

        void setParent (ClutterActor *parent);

        bool getVisible() const;
        void setVisible(bool value);

        bool isFill() const;
        void setFill(bool value);

        float getH() const;
        void setH(float value);

        float getW() const;
        void setW(float value);

        float getY() const;
        void setY(float value);

        float getX() const;
        void setX(float x);

        float getStrokeWidth() const;
        void setStrokeWidth(float value);

        float getStrokeDash() const;
        void setStrokeDash(float value);

        std::string getStrokeColor() const;
        void setStrokeColor(const std::string &value);

        std::string getFillColor() const;
        void setFillColor(const std::string &value);

private:

        ClutterActor *self;
//        ClutterActor *parent;

};

#endif // CIRCLE_H
