cmake_minimum_required(VERSION 3.5)

project(SimpleComputerShop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SimpleComputerShop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/alghoritms.cpp src/alghoritms.h src/cart.cpp src/cart.h src/case.cpp src/case.h src/component.cpp src/component.h src/configurator.cpp src/configurator.h src/cooler.cpp src/cooler.h src/cpu.cpp src/cpu.h src/employee.cpp src/employee.h src/gpu.cpp src/gpu.h src/main.cpp src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui src/motherboard.cpp src/motherboard.h src/order.cpp src/order.h src/power_unit.cpp src/power_unit.h src/ram.cpp src/ram.h src/rom.cpp src/rom.h src/stock.cpp src/stock.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SimpleComputerShop APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SimpleComputerShop SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SimpleComputerShop
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SimpleComputerShop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SimpleComputerShop)
endif()
set_target_properties(SimpleComputerShop PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SimpleComputerShop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SimpleComputerShop)
endif()
