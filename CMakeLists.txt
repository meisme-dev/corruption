cmake_minimum_required(VERSION 3.0.0)
project(Corruption VERSION 0.1.0)
file(GLOB Game
     "Source/*.hpp"
     "Source/*.cpp"
	 "Source/Engine/*.cpp"
	 "Source/Engine/*.hpp"
)

set(JOBS 4)
set(CMAKE_CXX_FLAGS "-g -O3")
add_executable(Game ${Game})

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/bgfx")
	message(FATAL_ERROR "bgfx submodule not found")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/bimg")
	message(FATAL_ERROR "bimg submodule not found")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/bx")
	message(FATAL_ERROR "bx submodule not found")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/glfw")
	message(FATAL_ERROR "glfw submodule not found")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/cpplocate")
	message(FATAL_ERROR "cpplocate submodule not found")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Libraries/box2d")
	message(FATAL_ERROR "box2d submodule not found")
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	set(RELEASE_TYPE "debug")
	set(RELEASE_TYPE_UPPER "Debug")
else()
	set(RELEASE_TYPE "release")
	set(RELEASE_TYPE_UPPER "Release")
endif()

if(UNIX)
	set(PLATFORM "linux")
	set(TARGET "gcc")
	set(EXTENSION ".sh")
elseif(APPLE)
	set(PLATFORM "osx")
	set(TARGET "clang")
	set(EXTENSION ".sh")
elseif(WIN32)
	set(PLATFORM "windows")
	set(TARGET "msvc")
	set(EXTENSION ".bat")
else()
	message(FATAL_ERROR "Unsupported platform")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES ".64")
	set(ARCH "64")
else()
	set(ARCH "32")
endif()

execute_process(COMMAND make ${PLATFORM}-${RELEASE_TYPE}${ARCH} -C bgfx -j${JOBS}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries
	RESULT_VARIABLE BGFX_BUILD_RESULT)
if(NOT BGFX_BUILD_RESULT EQUAL "0")
	message(FATAL_ERROR "bgfx build failed")
endif()

execute_process(COMMAND make ${PLATFORM}-${RELEASE_TYPE}${ARCH} -C bimg -j${JOBS}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries
	RESULT_VARIABLE BIMG_BUILD_RESULT)
if(NOT BIMG_BUILD_RESULT EQUAL "0")
	message(FATAL_ERROR "bimg build failed")
endif()

execute_process(COMMAND make ${PLATFORM}-${RELEASE_TYPE}${ARCH} -C bx -j${JOBS}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries
	RESULT_VARIABLE BX_BUILD_RESULT)
if(NOT BX_BUILD_RESULT EQUAL "0")
	message(FATAL_ERROR "bx build failed")
endif()

execute_process(COMMAND cmake -S . -B .build -DGLFW_USE_WAYLAND=ON
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries/glfw
	RESULT_VARIABLE GLFW_BUILD_RESULT)
if(NOT GLFW_BUILD_RESULT EQUAL "0")
	message(FATAL_ERROR "glfw build failed")
endif()

execute_process(COMMAND make -C .build -j${JOBS}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries/glfw
	RESULT_VARIABLE GLFW_BUILD_RESULT)
if(NOT GLFW_BUILD_RESULT EQUAL "0")
	message(FATAL_ERROR "glfw build failed")
endif()

execute_process(COMMAND cmake -S . -B .build
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries/cpplocate
	RESULT_VARIABLE CPPLOCATE_BUILD_RESULT)
if(NOT CPPLOCATE_BUILD_RESULT EQUAL "0")
	message(FATAL_ERROR "cpplocate build failed")
endif()

execute_process(COMMAND make -C .build -j${JOBS}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries/cpplocate
	RESULT_VARIABLE CPPLOCATE_BUILD_RESULT)
if(NOT CPPLOCATE_BUILD_RESULT EQUAL "0")
	message(FATAL_ERROR "cpplocate build failed")
endif()

execute_process(COMMAND /usr/bin/env bash -c \"${PROJECT_SOURCE_DIR}/Libraries/box2d/build${EXTENSION}\"
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Libraries/box2d
	RESULT_VARIABLE BOX2D_BUILD_RESULT)
if(NOT BOX2D_BUILD_RESULT EQUAL "0")
	message(FATAL_ERROR "box2d build failed")
endif()

execute_process(COMMAND cp -r ${PROJECT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	RESULT_VARIABLE ASSETS_COPY_RESULT)
if(NOT ASSETS_COPY_RESULT EQUAL "0")
	message(FATAL_ERROR "Assets copy failed")
endif()

target_link_directories(Game PRIVATE ${PROJECT_SOURCE_DIR}/Libraries/bgfx/.build/${PLATFORM}${ARCH}_${TARGET}/bin/)
target_link_directories(Game PRIVATE ${PROJECT_SOURCE_DIR}/Libraries/cpplocate/.build/)
target_link_directories(Game PRIVATE ${PROJECT_SOURCE_DIR}/Libraries/glfw/.build/src/)
target_link_directories(Game PRIVATE ${PROJECT_SOURCE_DIR}/Libraries/bgfx/examples/common)
target_link_directories(Game PRIVATE ${PROJECT_SOURCE_DIR}/Libraries/box2d/build)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/bgfx/include)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/bx/include)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/bimg/include)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/glfw/include)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/cpplocate/.build/source/cpplocate/include)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/cpplocate/source/cpplocate/include)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/box2d/include)
target_link_libraries(Game bgfx${RELEASE_TYPE_UPPER} bimg${RELEASE_TYPE_UPPER} bx${RELEASE_TYPE_UPPER} glfw3 GL X11 cpplocate)