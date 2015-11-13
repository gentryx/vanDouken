project(vandouken)
cmake_minimum_required(VERSION 2.8)

################################################################################
# enable solution folders for MSVC
if(MSVC)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()
################################################################################

find_package(OpenCV REQUIRED core videoio)
find_package(HPX REQUIRED)
find_package(libgeodecomp REQUIRED)

if(NOT HPX_NATIVE_MIC)
  find_package(Qt5Core REQUIRED)
  find_package(Qt5Gui REQUIRED)
  find_package(Qt5Widgets REQUIRED)
  find_package(Qt5OpenGL REQUIRED)
  find_package(Qt5Svg REQUIRED)
endif()

#find_package(Qt COMPONENTS QtOpenGL QtGui QtCore QtSvg)

#if(QT_FOUND)
#  include(${QT_USE_FILE})
#
#  add_definitions(-DQT_NO_KEYWORDS)
#endif()

include_directories(src)
include_directories(${CMAKE_BINARY_DIR}/src)
include_directories(${HPX_INCLUDE_DIR})
include_directories(${LIBGEODECOMP_INCLUDE_DIR})
include_directories(${OPENCV_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${LIBPNG_INCLUDE_DIR})

include_directories(${libgeodecomp_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${libgeodecomp_FLAGS}")

set(HPX_RPATH "${CMAKE_INSTALL_PREFIX}/lib/hpx:${CMAKE_BINARY_DIR}/lib/hpx:${LIBGEODECOMP_LIB_DIR}:${HPX_RPATH}")
link_directories(${CMAKE_BINARY_DIR}/lib/hpx)
link_directories(${HPX_LIBRARY_DIR})
link_directories(${LIBGEODECOMP_LIB_DIR})
link_directories(${ZLIB_LIB_DIR})
link_directories(${LIBPNG_LIB_DIR})
if("${HPX_PLATFORM}" STREQUAL "Android")
else()
    link_directories(${OPENCV_LIB_DIR})
    set(HPX_RPATH "${OPENCV_LIB_DIR}:${HPX_RPATH}")
endif()

if("${HPX_PLATFORM}" STREQUAL "Android")
    add_definitions("-DVANDOUKEN_DATA_DIR=\"://data/\"")
else()
    add_definitions("-DVANDOUKEN_DATA_DIR=\"${CMAKE_SOURCE_DIR}/data/\"")
endif()

add_subdirectory(src)
