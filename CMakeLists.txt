cmake_minimum_required(VERSION 4.1)

project(
        ${SKBUILD_PROJECT_NAME}
        VERSION ${SKBUILD_PROJECT_VERSION}
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

FetchContent_Declare(
        tzbot4cpp
        GIT_REPOSITORY https://github.com/m3z0id/TZBot4CPP.git
        GIT_TAG master
)

FetchContent_MakeAvailable(tzbot4cpp)

find_package(pybind11 CONFIG REQUIRED)

python_add_library(_core MODULE src/main.cpp src/exceptions.cpp src/data.cpp src/request.cpp WITH_SOABI)
target_link_libraries(_core PRIVATE pybind11::headers TZBot4CPP::TZBot4CPP)
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})

set_target_properties(_core PROPERTIES BUILD_RPATH "$ORIGIN" INSTALL_RPATH "$ORIGIN")

install(TARGETS _core DESTINATION tzbot4py)
install(TARGETS TZBot4CPP LIBRARY DESTINATION tzbot4py)
install(FILES
        "${CMAKE_SOURCE_DIR}/tzbot4py/__init__.py"
        "${CMAKE_SOURCE_DIR}/tzbot4py/py.typed"
        "${CMAKE_SOURCE_DIR}/tzbot4py/_core.pyi"
        DESTINATION tzbot4py
)