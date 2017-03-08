# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0 FATAL_ERROR)

PROJECT (data-flow-gui)
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)
INCLUDE (../tiliae/tiliae.cmake)
SET (CMAKE_VERBOSE_MAKEFILE OFF)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11" CACHE INTERNAL "cxx compiler flags")

SET(CMAKE_C_FLAGS_RELEASE "-DNDEBUG" CACHE INTERNAL "c release compiler flags")
SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG" CACHE INTERNAL "cxx release compiler flags")

ADD_DEFINITIONS (-DBOOST_LOG_DYN_LINK -DALLOW_CAST_TO_SMART -DUSE_ASSERT_THROW)

find_package (Boost REQUIRED COMPONENTS log log_setup regex)
include_directories(${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})

include (FindPkgConfig)

pkg_check_modules (TILIAE "tiliae")
if (NOT TILIAE_FOUND)
        MESSAGE (STATUS "Tiliae not installed, using local copy.")
        SET (TILIAE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../tiliae/src/")
        SET (TILIAE_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/../tiliae/build/src/")
        SET (TILIAE_LIBRARIES "tiliae")
        MESSAGE (STATUS ${TILIAE_INCLUDE_DIRS})
        MESSAGE (STATUS ${TILIAE_LIBRARY_DIRS})
endif ()
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
link_directories(${TILIAE_LIBRARY_DIRS})

pkg_check_modules (GTKFORMS "gtkforms")
if (NOT GTKFORMS_FOUND)
        MESSAGE (STATUS "GtkForms not installed, using local copy.")
        SET (GTKFORMS_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../gtkforms/src/")
        SET (GTKFORMS_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/../gtkforms/build/")
        SET (GTKFORMS_LIBRARIES "gtkforms")
        MESSAGE (STATUS ${GTKFORMS_INCLUDE_DIRS})
        MESSAGE (STATUS ${GTKFORMS_LIBRARY_DIRS})
endif ()
INCLUDE_DIRECTORIES (${GTKFORMS_INCLUDE_DIRS})
link_directories(${GTKFORMS_LIBRARY_DIRS})

pkg_check_modules (STATEMACHINE "state-machine")
if (NOT STATEMACHINE_FOUND)
        MESSAGE (STATUS "STATEMACHINE not installed, using local copy.")
        SET (STATEMACHINE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../state-machine/src/")
        SET (STATEMACHINE_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/../state-machine/build/src/")
        SET (STATEMACHINE_LIBRARIES "statemachine")
        MESSAGE (STATUS ${STATEMACHINE_INCLUDE_DIRS})
        MESSAGE (STATUS ${STATEMACHINE_LIBRARY_DIRS})
endif ()
INCLUDE_DIRECTORIES (${STATEMACHINE_INCLUDE_DIRS})
link_directories(${STATEMACHINE_LIBRARY_DIRS})

pkg_check_modules (DATAFLOW "data-flow")
if (NOT DATAFLOW_FOUND)
        MESSAGE (STATUS "DATAFLOW not installed, using local copy.")
        SET (DATAFLOW_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../data-flow/src/")
        SET (DATAFLOW_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/../data-flow/build/")
        SET (DATAFLOW_LIBRARIES "dataflow")
        MESSAGE (STATUS ${DATAFLOW_INCLUDE_DIRS})
        MESSAGE (STATUS ${DATAFLOW_LIBRARY_DIRS})
endif ()
INCLUDE_DIRECTORIES (${DATAFLOW_INCLUDE_DIRS})
link_directories(${DATAFLOW_LIBRARY_DIRS})

pkg_check_modules (GTK REQUIRED "gtk+-3.0")
INCLUDE_DIRECTORIES (${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

pkg_check_modules (CLUTTER_GTK REQUIRED "clutter-gtk-1.0")
INCLUDE_DIRECTORIES (${CLUTTER_GTK_INCLUDE_DIRS})
link_directories(${CLUTTER_GTK_LIBRARY_DIRS})

# +-------------------------------+
# | Generate reflection database. |
# +-------------------------------+
TILIAE_PARSE ("${PROJECT_SOURCE_DIR}/../tiliae/build/parser/tiliaeparser" "dataFlowGui" "src/Reflection_input.cc" "src/Reflection_output.cc.h")
LIST (APPEND SOURCES "src/Reflection_input.cc")
LIST (APPEND SOURCES "src/Reflection_output.cc.h")

# +-------------------------------+
# | Main target                   |
# +-------------------------------+

LIST (APPEND SOURCES
        "src/main.cc"
        "src/DataFlowApp.h"
        "src/DataFlowApp.cc"
        "src/gui/main/MainView.cc"
        "src/gui/main/MainView.h"
        "src/gui/main/IDrawingEventHandler.h"
        "src/gui/main/MainController.cc"
        "src/gui/main/MainController.h"
        "src/gui/main/Event.cc"
        "src/gui/main/Event.h"
        "src/gui/main/ContainerFactoryStrategy.cc"
        "src/gui/main/ContainerFactoryStrategy.h"
        "src/gui/main/ShapeDrawStrategy.cc"
        "src/gui/main/ShapeDrawStrategy.h"
        "src/gui/main/RectangularSelectorStrategy.cc"
        "src/gui/main/RectangularSelectorStrategy.h"
        "src/gui/main/ISelectorStrategy.h"
        "src/gui/main/DashedLineStrategy.cc"
        "src/gui/main/DashedLineStrategy.h"
        "src/gui/main/DashedLineConnectorStrategy.h"
        "src/gui/main/DashedLineConnectorStrategy.cc"
        "src/gui/main/IDrawStrategy.cc"
        "src/gui/main/IDrawStrategy.h"
        "src/gui/main/IFactoryStrategy.cc"
        "src/gui/main/IFactoryStrategy.h"
        "src/gui/main/MoveStrategy.cc"
        "src/gui/main/MoveStrategy.h"
        "src/gui/addNode/AddNodeController.cc"
        "src/gui/addNode/AddNodeController.h"
        "src/gui/addNode/AddNodeTableFilterMapping.cc"
        "src/gui/addNode/AddNodeTableFilterMapping.h"
        "src/view/clutter/drawing_stuff.c"
        "src/view/clutter/drawing_stuff.h"
        "src/view/clutter/iw_button.c"
        "src/view/clutter/iw_button.h"
        "src/view/clutter/iw_circle.c"
        "src/view/clutter/iw_circle.h"
        "src/view/clutter/iw_actor.c"
        "src/view/clutter/iw_actor.h"
        "src/view/clutter/iw_rectangle.c"
        "src/view/clutter/iw_rectangle.h"
        "src/view/clutter/iw_circular_node.c"
        "src/view/clutter/iw_circular_node.h"
        "src/view/clutter/iw_line.c"
        "src/view/clutter/iw_line.h"
        "src/view/clutter/iw_connector.c"
        "src/view/clutter/iw_connector.h"
        "src/view/Circle.h"
        "src/view/Circle.cc"
        "src/view/Rectangle.h"
        "src/view/Rectangle.cc"
        "src/view/RectangularSelector.h"
        "src/view/RectangularSelector.cc"
        "src/view/Line.h"
        "src/view/Line.cc"
        "src/view/Stage.h"
        "src/view/Stage.cc"
        "src/view/ScaleLayer.h"
        "src/view/ScaleLayer.cc"
        "src/view/CircularNode.h"
        "src/view/CircularNode.cc"
        "src/view/Button.h"
        "src/view/Button.cc"
        "src/view/Port.h"
        "src/view/Port.cc"
        "src/view/IClutterActor.h"
        "src/view/AbstractActor.h"
        "src/view/AbstractActor.cc"
        "src/view/IConnector.h"
        "src/view/Anchor.h"
        "src/view/Anchor.cc"
        "src/view/AbstractConnector.h"
        "src/view/AbstractConnector.cc"
        "src/view/LineConnector.h"
        "src/view/LineConnector.cc"
        "src/view/Connector.h"
        "src/view/Connector.cc"
        "src/view/INodeView.h"
        "src/view/AbstractNodeView.h"
        "src/view/AbstractNodeView.cc"
        "src/view/IArcView.h"
        "src/view/AbstractArcView.h"
        "src/view/AbstractArcView.cc"
        "src/primitives/Geometry.h"
        "src/primitives/Geometry.cc"
        "src/primitives/Color.h"
        "src/primitives/Color.cc"
        "src/primitives/Direction.h"
)

# Local includes (inside project).
INCLUDE_DIRECTORIES (src)
INCLUDE_DIRECTORIES ("/usr/include/libcxxabi")

add_executable (${CMAKE_PROJECT_NAME} ${SOURCES})

TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} c++abi)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} pthread)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${CLUTTER_GTK_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${GTK_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${GTKFORMS_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${STATEMACHINE_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${DATAFLOW_LIBRARIES})

ADD_CUSTOM_COMMAND (OUTPUT "${CMAKE_BINARY_DIR}/config.xml"
                    COMMAND ln -s "src/config.xml" "${CMAKE_BINARY_DIR}/config.xml"
                    DEPENDS "src/config.xml")

ADD_CUSTOM_COMMAND (OUTPUT "${CMAKE_BINARY_DIR}/ui"
                    COMMAND ln -s "ui" "${CMAKE_BINARY_DIR}/ui"
                    DEPENDS "ui")
