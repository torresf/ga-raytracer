# Install script for directory: /mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/c2ga/BasisTransformations.hpp;/usr/local/include/c2ga/Constants.hpp;/usr/local/include/c2ga/DualCoefficients.hpp;/usr/local/include/c2ga/Geometric.hpp;/usr/local/include/c2ga/GeometricExplicit.hpp;/usr/local/include/c2ga/Inner.hpp;/usr/local/include/c2ga/InnerExplicit.hpp;/usr/local/include/c2ga/Mvec.hpp;/usr/local/include/c2ga/Outer.hpp;/usr/local/include/c2ga/OuterExplicit.hpp;/usr/local/include/c2ga/Utility.hpp;/usr/local/include/c2ga/Mvec.cpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/c2ga" TYPE FILE FILES
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/BasisTransformations.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Constants.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/DualCoefficients.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Geometric.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/GeometricExplicit.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Inner.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/InnerExplicit.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Mvec.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Outer.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/OuterExplicit.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Utility.hpp"
    "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Mvec.cpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libc2ga.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libc2ga.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libc2ga.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libc2ga.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build/libc2ga.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libc2ga.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libc2ga.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libc2ga.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build/doc/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
