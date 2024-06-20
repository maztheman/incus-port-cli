cmake_minimum_required(VERSION 3.21..)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_EXTENSIONS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(incus-port-cli C CXX)

include(CPM)

cpmaddpackage(
      NAME restinio
      VERSION 0.7.2
      GITHUB_REPOSITORY "maztheman/restinio"
      GIT_TAG master
)

if(NOT TARGET fmt::fmt)
  cpmaddpackage("gh:fmtlib/fmt#10.2.1")
endif()

add_subdirectory(src)
