/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DataFlowApp.h"
#include <clutter-gtk/clutter-gtk.h>
#include <gtk/gtk.h>

//// TODO czemu to musi tu być? Czemu tiliaeparser zamienia bool na to _Bool?
#define _Bool bool
#include "Reflection_output.cc.h"
#include "Reflection_output_data_flow.cc.h"
#include "Reflection_output_gtkforms.cc.h"
#include "Reflection_output_tiliae.cc.h"

//#include <iostream>
//#include <thread>
//#include <tinyb.hpp>

// using namespace tinyb;

#include <functional>










/*****************************************************************************/

int main (int argc, char **argv)
{
#if 0
        BluetoothManager *manager = nullptr;

        try {
                manager = BluetoothManager::get_bluetooth_manager ();
        }
        catch (const std::runtime_error &e) {
                std::cerr << "Error while initializing libtinyb: " << e.what () << std::endl;
                exit (1);
        }

        std::cout << "API version : " << manager->get_api_version () << ", library version : " << manager->get_library_version () << std::endl;
        std::cout << "Class name : " << manager->get_class_name () << ", object path : " << manager->get_object_path () << std::endl;

        std::unique_ptr<BluetoothAdapter> adapter = manager->get_default_adapter ();
        std::cout << "Class name : " << adapter->get_class_name () << ", object path : " << adapter->get_object_path () << std::endl;

        // Start the discovery of devices */
        bool ret = manager->start_discovery ();

        if (!ret) {
                std::cout << "Failed to start discovery" << std::endl;
                return 1;
        }

        std::cout << "Discovering BLE devices" << std::endl;

        int num_devices = 0;
        bool no_new_devices = false;
        std::vector<std::unique_ptr<BluetoothDevice>> list_devices;
        BluetoothDevice *device = NULL;

        while (device == NULL && !no_new_devices) {
                list_devices = manager->get_devices ();

                if (list_devices.size () > 0 && list_devices.size () == num_devices) {
                        no_new_devices = true;
                }

                num_devices = list_devices.size ();

                // Look for active ESS device
                for (auto it = list_devices.begin (); it != list_devices.end (); ++it) {
                        std::unique_ptr<BluetoothDevice> dev = std::move (*it);

                        if (dev->get_rssi () != 0) {
                                std::cout << dev->get_alias () << std::endl;
                                auto list_uuids = dev->get_uuids ();

                                for (auto uuit = list_uuids.begin (); uuit != list_uuids.end (); ++uuit) {
                                        std::cout << *(uuit) << ", ";
                                }

                                device->
                        }

                        std::cout << std::endl;
                }

                if (device == NULL) {
                        std::this_thread::sleep_for (std::chrono::seconds (4));
                }
        }

        ret = manager->stop_discovery ();
        std::cout << std::endl;
#endif

        srand (time (0));

        if (gtk_clutter_init_with_args (&argc, &argv, NULL, NULL, NULL, NULL) != CLUTTER_INIT_SUCCESS) {
                g_error ("Unable to initialize GtkClutter");
        }

        DataFlowApp app;
        app.init ("config.xml", "mainController", { "../src", ".", "/usr/share/data-flow-gui" });
        gtk_main ();
}
