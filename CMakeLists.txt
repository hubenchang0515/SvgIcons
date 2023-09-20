cmake_minimum_required(VERSION 3.2)
project(SvgIcon)

find_package(
  Qt6
  COMPONENTS 
  Core
  Widgets
  Xml
  SvgWidgets
  REQUIRED)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOUIC ON)
SET(CXX_STANDARD 11)

add_subdirectory(3rdparty EXCLUDE_FROM_ALL)

set(ICON_MODULES ikonate)

function(aux_source_directory_append DIR VAR)
  file(GLOB SRC "${DIR}/*.cpp" "${DIR}/*.h" "${DIR}/*.qrc")
  set(${VAR} ${${VAR}} ${SRC} PARENT_SCOPE)
endfunction(aux_source_directory_append DIR VAR)

aux_source_directory_append("${CMAKE_CURRENT_SOURCE_DIR}/src/" SOURCE)
aux_source_directory_append("${CMAKE_CURRENT_SOURCE_DIR}/src/resource/" SOURCE)
aux_source_directory_append("${CMAKE_CURRENT_SOURCE_DIR}/src/module/" SOURCE)

foreach(MODULE ${ICON_MODULES})
  aux_source_directory_append("${CMAKE_CURRENT_SOURCE_DIR}/src/module/${MODULE}/" SOURCE)
endforeach(MODULE ${ICON_MODULES})

qt_add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC Qt6::Widgets Qt6::Xml Qt6::SvgWidgets zip)
target_link_directories(${PROJECT_NAME} PUBLIC Qt6::Widgets Qt6::Xml Qt6::SvgWidgets zip)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Widgets Qt6::Xml Qt6::SvgWidgets zip)