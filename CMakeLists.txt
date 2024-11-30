cmake_minimum_required(VERSION 3.16)

project(wangzhe_nongyao_qt_version2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        src/main.cpp
        src/LoginWindow.cpp
        src/LoginWindow.h
        src/LoginWindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(wangzhe_nongyao_qt_version2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/RegisterWindow.h src/RegisterWindow.cpp src/RegisterWindow.ui
        src/PrepareWindow.h src/PrepareWindow.cpp src/PrepareWindow.ui
        src/GameWindow.h src/GameWindow.cpp src/GameWindow.ui
        src/RankingWindow.h src/RankingWindow.cpp src/RankingWindow.ui
        src/core/Login.h src/core/Login.cpp
        src/core/Register.h src/core/Register.cpp
        src/core/Game.h src/core/Game.cpp
        src/core/Hero.h src/core/Hero.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET wangzhe_nongyao_qt_version2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(wangzhe_nongyao_qt_version2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(wangzhe_nongyao_qt_version2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(wangzhe_nongyao_qt_version2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.wangzhe_nongyao_qt_version2)
endif()
set_target_properties(wangzhe_nongyao_qt_version2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS wangzhe_nongyao_qt_version2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(wangzhe_nongyao_qt_version2)
endif()
