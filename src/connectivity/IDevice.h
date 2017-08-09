/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDEVICE_H
#define IDEVICE_H

#include <Program.h>
#include <functional>
#include <vector>

/**
 * A device (remote) which can interact with this GUI app, and with its data-flow (it has its own
 * data-flow engine build in).
 */
struct IDevice {
        virtual ~IDevice () {}

        /*---------------------------------------------------------------------------*/
        /* Firmware update                                                           */
        /*---------------------------------------------------------------------------*/

        enum FirmwareUpdateStatus { FW_OK, FW_TIMEOUT };
        void firmwareUpdate (uint8_t *data, size_t len);
        typedef std::function<void(FirmwareUpdateStatus, IDevice *)> FirmwareUpdateCallback;
        void setFirmwareUpdateCallback (FirmwareUpdateCallback f);
        typedef std::function<void(uint8_t, IDevice *)> FirmwareUpdateProgressCallback;
        void setFirmwareUpdateProgressCallback (FirmwareUpdateProgressCallback f);

        /*---------------------------------------------------------------------------*/
        /* Dataflow program upload/download                                          */
        /*---------------------------------------------------------------------------*/

        enum ProgramStatus { PGM_OK, PGM_TIMEOUT };
        void uploadProgram (flow::Program *program);
        flow::Program downloadProgram () const;
        typedef std::function<void(ProgramStatus, IDevice *, bool)> ProgramLoadCallback;
        void setProgramLoadCallback (ProgramLoadCallback f);
        typedef std::function<void(uint8_t, IDevice *, bool)> ProgramLoadProgressCallback;
        void setProgramLoadProgressCallback (ProgramLoadProgressCallback f);

        /*---------------------------------------------------------------------------*/
        /* Program manipulation                                                      */
        /*---------------------------------------------------------------------------*/

        virtual void run () = 0;
        virtual void step () = 0;
        virtual void reset () = 0;
};

typedef std::vector<IDevice *> DeviceVector;

#endif // IDEVICE_H
