/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTDEVICE_H
#define ABSTRACTDEVICE_H

#include "IDevice.h"

class AbstractDevice : public IDevice {
public:
        virtual ~AbstractDevice () {}
};

#endif // ABSTRACTDEVICE_H
