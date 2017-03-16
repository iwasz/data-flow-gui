/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ColorMapping.h"
#include "primitives/Color.h"

/*****************************************************************************/

void ColorMapping::setToView (GtkForms::ViewElementDTO *viewObject, std::string const &finalProperty, Core::Variant valueToSet)
{
        if (GTK_IS_COLOR_CHOOSER (viewObject->inputWidget)) {
                Color const *c = vcast<Color const *> (valueToSet);
                GdkRGBA rgba = Color::toGdkRGBA (*c);
                gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (viewObject->inputWidget), &rgba);
        }
        else {
                throw Core::Exception ("ColorMapping::setToView : widget type not supported. Supported types : GtkColorChooser.");
        }
}

/*****************************************************************************/

Core::Variant ColorMapping::getFromView (GtkForms::ViewElementDTO *viewObject, std::string const &finalProperty)
{
        GdkRGBA rgba;

        if (GTK_IS_COLOR_CHOOSER (viewObject->inputWidget)) {
                gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (viewObject->inputWidget), &rgba);
        }
        else {
                throw Core::Exception ("ColorMapping::getFromView : widget type not supported. Supported types : GtkColorChooser.");
        }

        return Core::Variant (Color (&rgba));
}
