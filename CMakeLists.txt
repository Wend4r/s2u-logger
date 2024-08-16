# Logger
# Copyright (C) 2023-2024 Wend4r
# Licensed under the GPLv3 license. See LICENSE file in the project root for details.

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

if(POLICY CMP0092)
	cmake_policy(SET CMP0092 NEW) # Don't add -W3 warning level by default.
endif()

project(s2u-logger
	VERSION 1.0.1
	DESCRIPTION "Logger"
	HOMEPAGE_URL "https://github.com/Wend4r/s2u-logger"
	LANGUAGES C CXX
)

string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)

set(PROJECT_OUTPUT_NAME "logger")

set(PROJECT_AUTHOR "Wend4r")
set(PROJECT_DESCRIPTION_FULL "Logger util for Source 2 games")
set(PROJECT_LICENSE "GPLv3")
string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d")
string(TIMESTAMP PROJECT_BUILD_TIME "%H:%M:%S")

set(EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

if(SOURCESDK_DIR)
	file(TO_CMAKE_PATH "${SOURCESDK_DIR}" SOURCESDK_DIR)
else()
	set(SOURCESDK_DIR "${EXTERNAL_DIR}/hl2sdk")
endif()

include("cmake/platform/shared.cmake")

if(LINUX)
	include("cmake/platform/linux.cmake")
elseif(WINDOWS)
	include("cmake/platform/windows.cmake")
endif()

include("cmake/sourcesdk.cmake")

set(SOURCE_FILES
	${SOURCE_DIR}/logger/detailed.cpp
	${SOURCE_DIR}/logger/message.cpp
	${SOURCE_DIR}/logger/warning.cpp
	${SOURCE_DIR}/logger/throw_assert.cpp
	${SOURCE_DIR}/logger/error.cpp
	${SOURCE_DIR}/logger/scope.cpp
	${SOURCE_DIR}/logger.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_EXTENSIONS OFF)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_OUTPUT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_OPTIONS} ${PLATFORM_COMPILER_OPTIONS})
target_link_options(${PROJECT_NAME} PRIVATE ${LINKER_OPTIONS} ${PLATFORM_LINKER_OPTIONS})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMPILE_DEFINITIONS} ${PLATFORM_COMPILE_DEFINITIONS} ${SOURCESDK_COMPILE_DEFINTIONS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR} ${SOURCESDK_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES} ${SOURCESDK_LINK_LIBRARIES})
