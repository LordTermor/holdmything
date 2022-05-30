cmake_minimum_required(VERSION 3.16)

project(holdmything VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
add_subdirectory(thirdparty/libfm-qt)

qt_add_executable(holdmything
    main.cpp
    QmlFileItem.h QmlFileItem.cpp
    QmlFileItemModel.h QmlFileItemModel.cpp
)

qt_add_qml_module(holdmything
    URI snitch
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(holdmything PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_include_directories(holdmything SYSTEM
    INTERFACE
        ${GIO_UNIX_INCLUDE_DIRS}
        ${GIO_INCLUDE_DIRS}
        ${GOBJECT_INCLUDE_DIRS}
        ${GLIB2_INCLUDE_DIRS}
    )
target_compile_definitions(holdmything
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG> QT_NO_KEYWORDS=1)



target_link_libraries(holdmything
    PUBLIC
    Qt6::Quick 
    fm-qt6
)
