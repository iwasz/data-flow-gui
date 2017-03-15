/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DFDIMENSIONRESTOREDATABASE_H
#define DFDIMENSIONRESTOREDATABASE_H

#include <decorator/DimensionRestoreDecorator.h>

class __tiliae_reflect__ DfDimensionRestoreDatabase : public GtkForms::DimensionRestoreDatabase {
public:
        virtual ~DfDimensionRestoreDatabase () { DfDimensionRestoreDatabase::save (); }
        virtual void load ();
        virtual void save ();
};

#endif // DFDIMENSIONRESTOREDATABASE_H
