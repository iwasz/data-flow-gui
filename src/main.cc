/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

/*
 * Peripherals that I could interface with.
 * - GPIO Analog input
 *  - Thermistor
 *  - Photoresistor
 *  - Potentiometer
 *
 * - GPIO digitali input (opcja debounce):
 *  - switches
 *  - LEDs
 *  - Relay
 *  - Buzzer (with built in oscillator)
 *
 * - PWM
 *  - Servo motor
 *  - RGB leds
 *
 * - Other
 *  - Ultrasonic proximity sensor (dedicated node for this).
 *  - Encoders
 *
 * - Advanced (would require complex custom nodes).
 *  - Dot matrix displays.
 *  - Stepper motor
 *  http://www.laser-shop.eu/arduino-platform/948-arduino-starter-kit-sensors-1423600378.html
 */

#include <clutter-gtk/clutter-gtk.h>
#include <gtk/gtk.h>
#include "DataFlowApp.h"

//// TODO czemu to musi tu być? Czemu tiliaeparser zamienia bool na to _Bool?
#define _Bool bool
#include "Reflection_output.cc.h"
#include "Reflection_output_gtkforms.cc.h"
#include "Reflection_output_tiliae.cc.h"
#include "Reflection_output_data_flow.cc.h"

/*****************************************************************************/

int main (int argc, char **argv)
{
        srand (time (0));

        if (gtk_clutter_init_with_args (&argc, &argv, NULL, NULL, NULL, NULL) != CLUTTER_INIT_SUCCESS) {
                g_error ("Unable to initialize GtkClutter");
        }

        DataFlowApp app;
        app.init ("config.xml", "mainController");
        gtk_main ();
}
