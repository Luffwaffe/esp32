cmake_minimum_required(VERSION 3.16)

project(App1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)
find_package(Qt6 REQUIRED COMPONENTS Sql)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appApp1
    main.cpp
)

qt_add_qml_module(appApp1
    URI App1
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES esp32connector.h esp32connector.cpp
        SOURCES cmdAndStatus.h
        SOURCES cardcontroller.h cardcontroller.cpp
        SOURCES databasecontroller.h databasecontroller.cpp
)

set_target_properties(appApp1 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appApp1
    PRIVATE Qt6::Quick Qt6::SerialPort Qt6::Sql

)

include(GNUInstallDirs)
install(TARGETS appApp1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
