/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEVICEREPOSITORY_H
#define DEVICEREPOSITORY_H

#include "IDevice.h"
#include "ITransport.h"
#include <functional>

class DeviceRepository {
public:
        void scan ();

        //        DeviceVector getAllDevices () const;

private:
        std::function<void(IDevice const &)> onNewDevice;
};

#endif // DEVICEREPOSITORY_H
