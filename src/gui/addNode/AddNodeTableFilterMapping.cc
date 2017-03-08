/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AddNodeTableFilterMapping.h"
#include "Logging.h"

static src::logger_mt &lg = logger::get ();

gboolean AddNodeTableFilterMapping::gtkTreeModelFilterVisibleFunc (GtkTreeModel *model, GtkTreeIter *iter, const Core::Variant &query)
{
        {
                GValue gVal = { 0 };

                gtk_tree_model_get_value (model, iter, 4, &gVal);
                gboolean isCategory = g_value_get_boolean (&gVal);

                if (isCategory) {
                        return true;
                }
        }

        GValue gVal = { 0 };
        gtk_tree_model_get_value (model, iter, 2, &gVal);
        const gchar *gStr = g_value_get_string (&gVal);

        if (!gStr) {
                return false;
        }

        std::string queryStr = vcast<std::string> (query);
        bool found = (std::string (gStr).find (queryStr) != std::string::npos);
        BOOST_LOG (lg) << "---- [" << query << "] =? [" << gStr << "], found = " << found;
        return found;
}
