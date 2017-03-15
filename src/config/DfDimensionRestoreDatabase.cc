/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DfDimensionRestoreDatabase.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

namespace pt = boost::property_tree;

std::string DfDimensionRestoreDatabase::getDirectory () const { return std::string (getenv ("HOME")) + "/.data-flow-gui"; }
std::string DfDimensionRestoreDatabase::getPath () const { return getDirectory () + "/dimensions.json"; }

/*****************************************************************************/

void DfDimensionRestoreDatabase::load ()
{
        pt::ptree tree;
        std::ifstream file (getPath (), std::ifstream::in);

        if (!file.is_open ()) {
                return;
        }

        pt::read_json (file, tree);

        for (auto &item : tree.get_child ("dimension")) {
                std::string dimensionKey = item.first;
#if 0
                std::cerr << dimensionKey << std::endl;
#endif
                for (auto &item2 : item.second.get_child ("")) {
                        double dimensionValue = item2.second.get_value<double> ();
#if 0
                        std::cerr << dimensionValue << std::endl;
#endif
                        values[dimensionKey].push_back (dimensionValue);
                }
        }
}

/*****************************************************************************/

void DfDimensionRestoreDatabase::save ()
{
        pt::ptree tree;

        for (ValueMap::value_type &v : values) {

                pt::ptree child;

                for (double d : v.second) {
                        pt::ptree tmp;
                        tmp.put ("", d);
                        child.push_back (pt::ptree::value_type ("", tmp));
                }

                tree.add_child ("dimension." + v.first, child);
        }

        boost::filesystem::path dir (getDirectory ());
        boost::filesystem::create_directory (dir);
        pt::write_json (getPath (), tree);
}
