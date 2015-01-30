project(adsp.parametric.eq)

cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(kodi REQUIRED)
find_package(kodiplatform REQUIRED)

include_directories(${kodiplatform_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/src/template)

set(TEMPLATE_SOURCES src/channelUpmixer.cpp
                     src/DSPProcessor.cpp
                     src/Dialogs/GUIDialogMasterProcess.cpp
                     src/Dialogs/GUIDialogOutputResample.cpp
                     src/Dialogs/GUIDialogPreProcess.cpp
                     src/Dialogs/GUIDialogPostProcess.cpp
                     src/ADDONOptional.cpp
                     src/template/client.cpp
                     src/template/GUIDialogBase.cpp
                     src/template/IADSPProcessor.cpp
                     src/template/ADSPProcessorHandle.cpp
                     src/template/IADDONOptional.cpp
                     src/template/configuration/templateConfiguration.cpp
                     src/template/ADSPAddonHandler.cpp)

set(DEPLIBS ${kodiplatform_LIBRARIES})

build_addon(adsp.parametric.eq TEMPLATE DEPLIBS)

# For generating the doxy
find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/doxygen_resources/Doxyfile
                    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                    COMMENT "Generating API documentation" VERBATIM)
endif()

include(CPack)
