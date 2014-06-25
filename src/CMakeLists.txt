#
# Virtualeyes cmake configuration
#
# Date Created: 2/3/11
# Author(s): Ben Becker (benjamin.becker@gmail.com)
#
###################################################

# Project setup
project(virtualeyes)

# Source files
SET(SRCS
        main.cpp
        virtualeyes.cpp
        core/handle_base.cpp
        core/vexcept.cpp
        core/debug.cpp
        core/store.cpp
        core/db/db.cpp
        core/db/realtime_feed.cpp
        core/enum_convert.cpp
        vm_iface/vm_iface.cpp
        breakpoint.cpp
        veye_scene.cpp
        main_view.cpp
        main_window.cpp
        memory_region.cpp
        session.cpp
        snapshot.cpp
        range_map.cpp
        console_widget.cpp
        console_input_widget.cpp
        vscript.cpp
        vm_run.cpp
        widgets/style_mgr.cpp
        widgets/abstract_hud_widget.cpp
        widgets/timeline_widget.cpp
        widgets/connection_widget.cpp
)

# Header files
SET(HDRS
        virtualeyes.hpp
        core/debug.hpp
        core/common.hpp
        core/handle.hpp
        core/soft_handle.hpp
        core/handle_base.hpp
        core/target_host.hpp
        core/vexcept.hpp
        core/global.hpp
        core/store.hpp
        core/db/db.hpp
        core/db/realtime_feed.hpp
        core/enum_convert.hpp
        vm_iface/vm_iface.hpp
        models/x86_32.hpp
        opsys/win2k8.hpp
        opsys/os_none.hpp
        range_map.hpp
        breakpoint.hpp
        veye_scene.hpp
        main_window.hpp
        main_view.hpp
        memory_region.hpp
        session.hpp
        snapshot.hpp
        console_widget.hpp
        console_input_widget.hpp
        vscript.hpp
        vm_run.hpp
        widgets/style_mgr.hpp
        widgets/abstract_hud_widget.hpp
        widgets/timeline_widget.hpp
        widgets/connection_widget.hpp
)

# Compile Qt metaobjects and forms
#QT4_WRAP_UI(UI_SRCS main_window.ui)
QT4_WRAP_CPP(MOC_SRCS main_window.hpp
                      main_view.hpp
                      veye_scene.hpp
                      session.hpp
                      range_map.hpp
                      virtualeyes.hpp
                      console_widget.hpp
                      console_input_widget.hpp
                      snapshot.hpp
                      widgets/abstract_hud_widget.hpp
                      widgets/timeline_widget.hpp
                      widgets/connection_widget.hpp
                      core/db/db.hpp
                      core/db/realtime_feed.hpp
)

SET(VEYE_RESOURCES
        ${CMAKE_SOURCE_DIR}/resources/icons.qrc
)

QT4_ADD_RESOURCES(ASSET_SRCS ${VEYE_RESOURCES})

SET(SRCS ${SRCS} ${MOC_SRCS} ${UI_SRCS})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/src/core
                    ${CMAKE_SOURCE_DIR}/src/vm_iface
                    ${CMAKE_SOURCE_DIR}/src/models
                    ${CMAKE_SOURCE_DIR}/src/opsys
                    ${QT_INCLUDES}
                    ${OPENGL_INCLUDE_DIR}
                    ${CMAKE_SOURCE_DIR}/../mongo
)

# platform-specific executable targets
IF(UNIX)
        IF(APPLE)
                # MacOS Application Bundle
                # include_directories()
                add_executable(virtualeyes MACOSX_BUNDLE ${HDRS} ${SRCS} ${UI_H} ${ASSET_SRCS})
        ELSE()
                # Linux Executable
                add_executable(virtualeyes ${HDRS} ${SRCS} ${UI_H} ${ASSET_SRCS})
        ENDIF(APPLE)
ELSE(UNIX)
        IF(WIN32)
                # Windows Executable
                add_executable(virtualeyes ${HDRS} ${SRCS} ${UI_H} ${ASSET_SRCS})
        ENDIF(WIN32)
ENDIF(UNIX)

# link libs to executable
TARGET_LINK_LIBRARIES(virtualeyes
                      ${QT_LIBRARIES}
                      ${OPENGL_LIBRARIES}
                      -L${CMAKE_SOURCE_DIR}/../mongo/
                      mongoclient
                      boost_thread-mt
                      boost_filesystem-mt
                      boost_system-mt
                      # -L/opt/local/lib/      # for macports
                      # tcmalloc
                      # profiler
)

# set the installer
INSTALL(TARGETS virtualeyes DESTINATION bin)
