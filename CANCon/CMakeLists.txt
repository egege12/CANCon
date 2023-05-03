cmake_minimum_required(VERSION 3.16)
list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.5.0/gcc_64")
project(CANCon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick SerialBus)
qt_standard_project_setup()

qt_add_executable(appCANCon
    main.cpp
    canSocket.h
)

qt_add_qml_module(appCANCon
    URI CANCon
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(appCANCon PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCANCon
    PRIVATE Qt6::Quick
    PRIVATE Qt6::SerialBus
)

install(TARGETS appCANCon
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
