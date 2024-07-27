cmake_minimum_required(VERSION 3.5)

project(ComputerAccounting VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)                               # Для базы данных
#find_package(Qt5 REQUIRED COMPONENTS Sql)                               # Для базы данных

if (WIN32)
    #find_package(wbemuuid)                                                 # Для WMI
endif()

set(PROJECT_SOURCES
        main.cpp
       mainWindow.cpp
       mainWindow.h
       mainWindow.ui
       computerdata.h
       computerdata.cpp
       computerdata.ui
       infoWin.h
       infoWin.cpp
       infoLin.h
       infoLin.cpp
       smbios.h
       smbios.cpp
       infoPlatform.h
       infoPlatform.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ComputerAccounting
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        smbios.h smbios.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ComputerAccounting APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ComputerAccounting SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ComputerAccounting
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ComputerAccounting PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(ComputerAccounting PRIVATE Qt5::Sql)                          # Для базы данных
target_link_libraries(ComputerAccounting PRIVATE Qt6::Sql)                          # Для базы данных

if (WIN32)
    target_link_libraries(ComputerAccounting PRIVATE dxgi)                              # DirectX API wbemuuid
    target_link_libraries(ComputerAccounting PRIVATE wbemuuid)                          # Для WMI
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ComputerAccounting)
endif()
set_target_properties(ComputerAccounting PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

# ADD_EXECUTABLE(_main main.cpp
#                     mainWindow.cpp mainWindow.h mainWindow.ui
#                     computerdata.h computerdata.cpp computerdata.ui
#               )
# ADD_EXECUTABLE(Info infoWin.h infoWin.cpp infoLin.h infoLin.cpp)
# ADD_EXECUTABLE(linux infoLin.h infoLin.cpp)
# ADD_EXECUTABLE(smbios smbios.h smbios.cpp)

install(TARGETS ComputerAccounting
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ComputerAccounting)
endif()
