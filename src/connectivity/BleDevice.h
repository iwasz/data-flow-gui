/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BLEDEVICE_H
#define BLEDEVICE_H

#include "AbstractDevice.h"

class BleDevice : public AbstractDevice {
public:
        virtual ~BleDevice () {}
};

#endif // BLEDEVICE_H
