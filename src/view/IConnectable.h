/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONNECTABLE_H
#define ICONNECTABLE_H

/**
 * Every (drawable) object which IConnector can connect to.
 */
struct IConnectable {
        virtual ~IConnectable () {}
};

#endif // ICONNECTABLE_H
