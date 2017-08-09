# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0048 NEW)
endif(COMMAND cmake_policy)

PROJECT (data-flow-gui VERSION 0.1)
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)
INCLUDE (../tiliae/tiliae.cmake)
SET (CMAKE_VERBOSE_MAKEFILE OFF)
SET (CMAKE_INSTALL_PREFIX /usr)
SET (WITH_PARSER               ON CACHE BOOL "")
SET (WITH_CPPABI               ON CACHE BOOL "")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11" CACHE INTERNAL "cxx compiler flags")
IF (WIN32)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
ENDIF ()


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

pkg_check_modules (MXML REQUIRED "mxml")
INCLUDE_DIRECTORIES (${MXML_INCLUDE_DIRS})
link_directories(${MXML_LIBRARY_DIRS})

pkg_check_modules (AVOID REQUIRED "libavoid")
INCLUDE_DIRECTORIES (${AVOID_INCLUDE_DIRS})
link_directories(${AVOID_LIBRARY_DIRS})

pkg_check_modules (TINYB REQUIRED "tinyb")
INCLUDE_DIRECTORIES (${TINYB_INCLUDE_DIRS})
link_directories(${TINYB_LIBRARY_DIRS})

# +-------------------------------+
# | Generate reflection database. |
# +-------------------------------+
IF (WITH_PARSER)
TILIAE_PARSE ("${PROJECT_SOURCE_DIR}/../tiliae/build/parser/tiliaeparser" "dataFlowGui" "src/Reflection_input.cc" "src/Reflection_output.cc.h")
ENDIF ()
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
        "src/gui/main/Tool.cc"
        "src/gui/main/Tool.h"
        "src/gui/addNode/AddNodeController.cc"
        "src/gui/addNode/AddNodeController.h"
        "src/gui/addNode/AddNodeTableFilterMapping.cc"
        "src/gui/addNode/AddNodeTableFilterMapping.h"
        "src/gui/console/ConsoleController.cc"
        "src/gui/console/ConsoleController.h"
        "src/gui/console/ConsoleView.cc"
        "src/gui/console/ConsoleView.h"
        "src/gui/console/ConsoleBuffer.cc"
        "src/gui/console/ConsoleBuffer.h"
        "src/gui/properties/PropertiesController.cc"
        "src/gui/properties/PropertiesController.h"
        "src/gui/properties/DoubleToFloatEditor.h"
        "src/gui/saveLoadFile/OpenFileController.h"
        "src/gui/saveLoadFile/OpenFileController.cc"
        "src/gui/saveLoadFile/SaveFileController.h"
        "src/gui/saveLoadFile/SaveFileController.cc"
        "src/gui/saveLoadFile/IDataFileSave.h"
        "src/gui/saveLoadFile/IDataFileLoad.h"
        "src/gui/saveLoadFile/NativeXmlFormatSave.h"
        "src/gui/saveLoadFile/NativeXmlFormatSave.cc"
        "src/gui/saveLoadFile/NativeXmlFormatLoad.h"
        "src/gui/saveLoadFile/NativeXmlFormatLoad.cc"
        "src/view/clutter/drawing_stuff.c"
        "src/view/clutter/drawing_stuff.h"
        "src/view/clutter/iw_button.c"
        "src/view/clutter/iw_button.h"
        "src/view/clutter/iw_circle.c"
        "src/view/clutter/iw_circle.h"
        "src/view/clutter/iw_ellipse.c"
        "src/view/clutter/iw_ellipse.h"
        "src/view/clutter/iw_simple_display.c"
        "src/view/clutter/iw_simple_display.h"
        "src/view/clutter/iw_actor.c"
        "src/view/clutter/iw_actor.h"
        "src/view/clutter/iw_rectangle.c"
        "src/view/clutter/iw_rectangle.h"
        "src/view/clutter/iw_abstract_node.c"
        "src/view/clutter/iw_abstract_node.h"
        "src/view/clutter/iw_circular_node.c"
        "src/view/clutter/iw_circular_node.h"
        "src/view/clutter/iw_line.c"
        "src/view/clutter/iw_line.h"
        "src/view/clutter/iw_connector.c"
        "src/view/clutter/iw_connector.h"
        "src/view/Circle.h"
        "src/view/Circle.cc"
        "src/view/Ellipse.h"
        "src/view/Ellipse.cc"
        "src/view/SimpleDisplay.h"
        "src/view/SimpleDisplay.cc"
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
        "src/view/Connector.h"
        "src/view/Connector.cc"
        "src/view/ConnectorActor.h"
        "src/view/ConnectorActor.cc"
        "src/view/NodeActor.h"
        "src/view/NodeActor.cc"
        "src/view/INodeView.h"
        "src/view/AbstractNodeView.h"
        "src/view/AbstractNodeView.cc"
        "src/view/IArcView.h"
        "src/view/AbstractArcView.h"
        "src/view/AbstractArcView.cc"
        "src/view/SceneAPI.h"
        "src/view/SceneAPI.cc"
        "src/primitives/Geometry.h"
        "src/primitives/Geometry.cc"
        "src/primitives/Color.h"
        "src/primitives/Color.cc"
        "src/primitives/Direction.h"
        "src/primitives/Direction.cc"
        "src/primitives/Line.h"
        "src/primitives/Line.cc"
        "src/primitives/Ray.h"
        "src/primitives/Ray.cc"
        "src/primitives/PrimitiveOperations.h"
        "src/primitives/PrimitiveOperations.cc"
        "src/customNode/ConsoleNode.h"
        "src/customNode/ConsoleNode.cc"
        "src/customNode/DisplayNode.h"
        "src/customNode/DisplayNode.cc"
        "src/config/UserConfig.h"
        "src/config/UserConfig.cc"
        "src/config/DfDimensionRestoreDatabase.cc"
        "src/config/DfDimensionRestoreDatabase.h"
        "src/mapping/ColorMapping.h"
        "src/mapping/ColorMapping.cc"
        "src/view/routable/IRoutable.h"
        "src/view/routable/AbstractRoutable.h"
        "src/view/routable/AbstractRoutable.cc"
        "src/view/routable/RoutableRoot.h"
        "src/view/routable/RoutableRoot.cc"
        "src/view/routable/NodeRoutable.h"
        "src/view/routable/ObstacleRoutable.h"
        "src/view/routable/ConnectorRoutable.h"
        "src/view/routable/ConnectorRoutable.cc"
        "src/view/routable/RoutablePin.h"
        "src/view/routable/RoutablePin.cc"
        "src/connectivity/IDevice.h"
        "src/connectivity/AbstractDevice.h"
        "src/connectivity/AbstractDevice.cc"
        "src/connectivity/BleDevice.h"
        "src/connectivity/BleDevice.cc"
        "src/connectivity/ITransport.h"
        "src/connectivity/BleTransport.h"
        "src/connectivity/BleTransport.cc"
        "src/connectivity/LocalTransport.h"
        "src/connectivity/LocalTransport.cc"
        "src/connectivity/DeviceRepository.h"
        "src/connectivity/DeviceRepository.cc"
)

# Local includes (inside project).
INCLUDE_DIRECTORIES (src)
INCLUDE_DIRECTORIES ("/usr/include/libcxxabi")

add_executable (${CMAKE_PROJECT_NAME} ${SOURCES})

IF (WITH_CPPABI)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} c++abi)
ENDIF ()
IF (BUILD_SHARED_LIBS)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${GTKFORMS_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${MXML_LIBRARIES})
ELSE ()
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} libgtkforms.a)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} libtiliae.a)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${MXML_LIBRARIES})
ENDIF ()
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${STATEMACHINE_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${DATAFLOW_LIBRARIES})

TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${AVOID_STATIC_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${TINYB_STATIC_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${CLUTTER_GTK_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${GTK_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} pthread)


INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/src/"
    DESTINATION "share/data-flow-gui"
    FILES_MATCHING
    PATTERN "*.ui"
    PATTERN "*.xml"
    PATTERN "*.png"
    PATTERN "*.jpg"
    PATTERN "*.svn*" EXCLUDE
    PATTERN "*.git*" EXCLUDE
    PATTERN "*test*" EXCLUDE)

INSTALL (
    TARGETS data-flow-gui
    DESTINATION bin
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)

ADD_CUSTOM_TARGET("publish" DEPENDS data-flow-gui COMMAND rm -Rf /tmp/installdir)
ADD_CUSTOM_COMMAND(TARGET "publish" COMMAND mkdir -p /tmp/installdir)
ADD_CUSTOM_COMMAND(TARGET "publish" COMMAND make install DESTDIR=/tmp/installdir)

FIND_PROGRAM (FPM fpm)
ADD_CUSTOM_COMMAND (TARGET "publish" COMMAND ${FPM} -f -s dir -t deb -n data-flow-gui -v ${PROJECT_VERSION} -C /tmp/installdir/ -p data-flow-gui_VERSION_ARCH.deb -d 'libgtkforms >= 0.9' -d 'libclutter-gtk-1.0-0 >= 1.8.0' usr)
FIND_PROGRAM (DPKGSIG dpkg-sig)
ADD_CUSTOM_COMMAND (TARGET "publish" COMMAND ${DPKGSIG} -k 9EDE3F68 -s builder *.deb)
FIND_PROGRAM (SCP scp)
ADD_CUSTOM_COMMAND (TARGET "publish" COMMAND ${SCP} data-flow-gui_${PROJECT_VERSION}_amd64.deb iwasz@iwasz.pl:/home/iwasz/domains/iwasz.pl/public_html/deb/)

