cmake_minimum_required(VERSION 3.16)

project(holdmything VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Quick Widgets REQUIRED)
find_package(LayerShellQt REQUIRED)


qt_add_resources(holdmything_resources
    qml.qrc)

add_executable(holdmything
    main.cpp
    QmlFileItem.h QmlFileItem.cpp
    QmlFileItemModel.h QmlFileItemModel.cpp
    ${holdmything_resources}
)

set_target_properties(holdmything PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_compile_definitions(holdmything
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG> QT_NO_KEYWORDS=1)



target_link_libraries(holdmything
    PUBLIC
    Qt5::Quick 
    Qt5::Widgets
    LayerShellQt::Interface
    fm-qt
)
