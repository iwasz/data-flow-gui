#!/bin/bash

cd /home/iwasz/workspace/gtkforms-demo
find src/ -name '*.cc' -o -name '*.h' | grep -v 'Reflection_' | awk -- '{ print "LIST (APPEND SOURCES \"" $1 "\")"; }'
