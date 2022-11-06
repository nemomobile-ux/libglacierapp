option(USE_QT6 "Build with Qt6 support" OFF)
if(USE_QT6)
    set(QT_PKG_VER 6)
    set(LIBGLACIER_PKG_VER "6")
    add_definitions(-DHAVE_QT6)
else()
    set(LIBGLACIER_PKG_VER "")
    set(QT_PKG_VER 5)
    add_definitions(-DHAVE_QT5)
endif()


#Macro to wrap cpp files
macro(qt_wrap_cpp RESULT _CPP_FILES)
    if(USE_QT6)
        qt6_wrap_cpp(MOC_FILES "${_CPP_FILES}")
    else()
        qt5_wrap_cpp(MOC_FILES "${_CPP_FILES}")
    endif()
    set(${RESULT} ${MOC_FILES})
endmacro()

#Macro to compile qt resources
macro(qt_add_resources RESULT _RES_FILES)
    if(USE_QT6)
        qt6_add_resources(OUTPUT_FILES "${_RES_FILES}")
    else()
        qt5_add_resources(OUTPUT_FILES "${_RES_FILES}")
    endif()
    set(${RESULT} ${OUTPUT_FILES})
endmacro()

#Macro to wrap qt ui-files
macro(qt_wrap_ui RESULT _UI_FILES)
    if(USE_QT6)
        qt6_wrap_ui(OUTPUT_UIS ${_UI_FILES})
    else()
        qt5_wrap_ui(OUTPUT_UIS ${_UI_FILES})
    endif()
    set(${RESULT} ${OUTPUT_UIS})
endmacro()

#Macro to compile qt transalations
macro(qt_add_translation RESULT _TRS_FILES)
    if(USE_QT6)
        qt6_add_translation(OUTPUT_TRS ${_TRS_FILES})
    else()
        qt5_add_translation(OUTPUT_TRS ${_TRS_FILES})
    endif()
    set(${RESULT} ${OUTPUT_TRS})
endmacro()

#Macro to find qt packages
macro(find_qt_package _PKG_LIST _OPTIONS)
    find_package(Qt${QT_PKG_VER} COMPONENTS ${_PKG_LIST} ${_OPTIONS})
endmacro()

#Macro to add qt libraries to list
macro(add_qt_library RESULT _LIBRARIES)
    foreach(LIBRARY ${_LIBRARIES})
        list(APPEND ${RESULT} Qt${QT_PKG_VER}::${LIBRARY})
    endforeach()
endmacro()
