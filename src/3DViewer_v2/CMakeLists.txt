cmake_minimum_required(VERSION 3.5)

project(3DViewer_v2 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MACOSX_BUNDLE_ICON_FILE cat.icns)
set(app_icon_macos ${CMAKE_CURRENT_SOURCE_DIR}/resources/images/cat.icns)
set(ICON_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/3DViewer_v2.app/Contents/Resources/)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)


# find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
# find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cc
        view/view.cc view/view.h view/view.ui
        view/oglwidget.h view/oglwidget.cc
        model/parser.cc model/parser.h
        model/point.h model/facet.h
        controller/controller.cc controller/controller.h
        model/model.cc model/model.h
        model/affine_transform_utils.cc model/affine_transform_utils.h
        resources/resources.qrc
        controller/adapter.h controller/adapter.cc
        model/iterable_vector.h
        library/GIF/qgifimage_p.h
        library/GIF/qgifimage.h
        library/GIF/qgifimage.cpp
        library/GIF/qgifglobal.h
        library/GIF/dgif_lib.c
        library/GIF/egif_lib.c
        library/GIF/gif_err.c
        library/GIF/gif_font.c
        library/GIF/gif_hash.c
        library/GIF/gif_hash.h
        library/GIF/gif_lib.h
        library/GIF/gif_lib_private.h
        library/GIF/gifalloc.c
        library/GIF/quantize.c
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer_v2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer_v2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer_v2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer_v2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewer_v2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
# target_link_libraries(3DViewer_v2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets -lGL -lglut -lGLU)

file(COPY ${app_icon_macos} DESTINATION ${ICON_DESTINATION})

set_target_properties(3DViewer_v2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/resources/Info.plist
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer_v2)
endif()
