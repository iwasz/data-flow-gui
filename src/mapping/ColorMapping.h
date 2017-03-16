/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COLORMAPPING_H
#define COLORMAPPING_H

#include <ReflectionParserAnnotation.h>
#include <mapping/Mapping.h>

class __tiliae_reflect__ ColorMapping : public GtkForms::Mapping {
public:
        virtual ~ColorMapping () {}

protected:
        virtual void setToView (GtkForms::ViewElementDTO *viewObject, std::string const &finalProperty, Core::Variant valueToSet);
        virtual Core::Variant getFromView (GtkForms::ViewElementDTO *viewObject, std::string const &finalProperty);
};

#endif // COLORMAPPING_H
