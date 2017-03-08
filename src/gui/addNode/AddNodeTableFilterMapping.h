/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#ifndef ADDNODETABLEFILTERMAPPING_H
#define ADDNODETABLEFILTERMAPPING_H

#include <mapping/TableFilterMapping.h>

class __tiliae_reflect__ AddNodeTableFilterMapping : public GtkForms::TableFilterMapping {
public:
        virtual ~AddNodeTableFilterMapping () {}
        virtual gboolean gtkTreeModelFilterVisibleFunc (GtkTreeModel *model, GtkTreeIter *iter, const Core::Variant &query) __tiliae_no_reflect__;
};

#endif // ADDNODETABLEFILTERMAPPING_H
