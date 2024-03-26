cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

if(POLICY CMP0092)
	cmake_policy(SET CMP0092 NEW) # Don't add -W3 warning level by default.
endif()

project(logger
	VERSION 1.0.0
	DESCRIPTION "Logger"
	HOMEPAGE_URL "https://github.com/Wend4r/s2u-logger"
	LANGUAGES C CXX
)

if(NOT SOURCESDK_DIR)
	message(WARNING "SOURCESDK_DIR is empty")
	set(SOURCESDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../hl2sdk-wend4r/hl2sdk-cs2)
endif()

set(INCLUDE_DIR "include")
set(SOURCE_DIR "src")

include("cmake/platform/shared.cmake")

if(LINUX)
	include("cmake/platform/linux.cmake")
elseif(WINDOWS)
	include("cmake/platform/windows.cmake")
endif()

include("cmake/sourcesdk.cmake")

set(SOURCE_FILES
	${SOURCE_DIR}/${PROJECT_NAME}/detailed.cpp
	${SOURCE_DIR}/${PROJECT_NAME}/message.cpp
	${SOURCE_DIR}/${PROJECT_NAME}/warning.cpp
	${SOURCE_DIR}/${PROJECT_NAME}/throw_assert.cpp
	${SOURCE_DIR}/${PROJECT_NAME}/error.cpp
	${SOURCE_DIR}/${PROJECT_NAME}/scope.cpp
	${SOURCE_DIR}/${PROJECT_NAME}.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SOURCESDK_LIBRARIES})
