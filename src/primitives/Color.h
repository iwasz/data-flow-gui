/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PRIMITIVES_COLOR_H
#define PRIMITIVES_COLOR_H

#include <clutter-gtk/clutter-gtk.h>
#include <cstdint>
#include <editor/IEditor.h>
#include <string>

class Color {
public:
        Color () : r (255), g (255), b (255), a (255) {}
        Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r (r), g (g), b (b), a (a) {}
        explicit Color (std::string const &col) { *this = fromString (col); }
        explicit Color (ClutterColor *cc) { *this = fromClutterColor (cc); }

        uint8_t getR () const { return r; }
        void setR (const uint8_t &value) { r = value; }

        uint8_t getG () const { return g; }
        void setG (const uint8_t &value) { g = value; }

        uint8_t getB () const { return b; }
        void setB (const uint8_t &value) { b = value; }

        uint8_t getA () const { return a; }
        void setA (const uint8_t &value) { a = value; }

        static Color fromString (std::string const &s);
        static std::string toString (Color const &c);
        static Color fromClutterColor (ClutterColor *cc);
        static ClutterColor toClutterColor (Color const &c);
        std::string toString () const { return toString (*this); }
        ClutterColor toClutterColor () const { return toClutterColor (*this); }

private:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
};

/*****************************************************************************/

/**
 * Klasa konwertująca string na różne typy.
 */
class ColorEditor : public Editor::IEditor {
public:
        virtual ~ColorEditor () {}

        /**
         * @param input Konwertowalny na Core::String.
         * @param output Wskaźnik do dowolnego wariantu (może być isNone ()).
         */
        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);
};


#endif // COLOR_H
