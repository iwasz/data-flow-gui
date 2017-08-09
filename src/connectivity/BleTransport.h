/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BLETRANSPORT_H
#define BLETRANSPORT_H

#include "IDevice.h"
#include "ITransport.h"
#include <functional>

class BleTransport : public ITransport {
public:
        void scan ();
        DeviceVector getAllDevices () const;

        typedef std::function<void(IDevice *)> NewDeviceCallback;
        void setNewDeviceCallback (NewDeviceCallback f) { onNewDevice = f; }

private:
        NewDeviceCallback onNewDevice;
};

#endif // BLETRANSPORT_H
