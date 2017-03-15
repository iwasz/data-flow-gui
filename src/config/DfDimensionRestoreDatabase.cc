/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DfDimensionRestoreDatabase.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

namespace pt = boost::property_tree;

void DfDimensionRestoreDatabase::load ()
{
        pt::ptree tree;
        std::ifstream file ("data.json", std::ifstream::in);
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

        // Write property tree to XML file
        pt::write_json ("data.json", tree);
}
