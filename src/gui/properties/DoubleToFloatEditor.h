/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DOUBLETOFLOATEDITOR_H
#define DOUBLETOFLOATEDITOR_H

#include <cassert>
#include <core/variant/Cast.h>
#include <core/variant/Variant.h>
#include <editor/IEditor.h>

/**
 * Edytory dzialaja w jedna strone, nie tak jak w javie.
 * Ten konwertuje stringa do MegaTona.
 */
struct __tiliae_reflect__ DoubleToFloatEditor : public Editor::IEditor {

        virtual ~DoubleToFloatEditor () {}

        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *)
        {
                double d = vcast<double> (input);
                *output = Core::Variant (float(d));
                return true;
        }
};

#endif // DOUBLETOFLOATEDITOR_H
