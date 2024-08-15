# {project}
# Copyright (C) {year} {name of author}
# Licensed under the GPLv3 license. See LICENSE file in the project root for details.

if(NOT SOURCESDK_DIR)
	message(FATAL_ERROR "SOURCESDK_DIR is empty")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
	set(SOURCESDK_COMPILE_DEFINTIONS
		${SOURCESDK_COMPILE_DEFINTIONS}

		-DPLATFORM_64BITS -DX64BITS
	)
else()
	set(SIZEOF_BITS ${CMAKE_SIZEOF_VOID_P})
	math(EXPR SIZEOF_BITS "${SIZEOF_BITS}*8")
	message(FATAL_ERROR "${SIZEOF_BITS}-bit platform is not supported")
endif()

if(LINUX)
	set(SOURCESDK_COMPILE_DEFINTIONS
		${SOURCESDK_COMPILE_DEFINTIONS}

		-DPOSIX
		-D_LINUX -DLINUX

		-Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp
		-Dstrnicmp=strncasecmp -D_snprintf=snprintf
		-D_vsnprintf=vsnprintf -D_alloca=alloca -Dstrcmpi=strcasecmp
	)
endif()

if(WINDOWS)
	set(SOURCESDK_COMPILE_DEFINTIONS
		${SOURCESDK_COMPILE_DEFINTIONS}

		-D_WIN32 -DWIN32
	)
endif()

if(MSVC)
	set(SOURCESDK_COMPILE_DEFINTIONS
		${SOURCESDK_COMPILE_DEFINTIONS}

		-DCOMPILER_MSVC -DCOMPILER_MSVC64
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(PLATFORM_COMPILE_DEFINITIONS
		${PLATFORM_COMPILE_DEFINITIONS}

		-D_DEBUG -DDEBUG
	)
endif()

set(SOURCESDK_INCLUDE_DIR
	${SOURCESDK_INCLUDE_DIR}

	${SOURCESDK_DIR}/common
	${SOURCESDK_DIR}/game/shared
	${SOURCESDK_DIR}/game/server
	${SOURCESDK_DIR}/public/engine
	${SOURCESDK_DIR}/public/entity2
	${SOURCESDK_DIR}/public/game/server
	${SOURCESDK_DIR}/public/mathlib
	${SOURCESDK_DIR}/public/tier0
	${SOURCESDK_DIR}/public/tier1
	${SOURCESDK_DIR}/public
	${SOURCESDK_DIR}
)

set(SOURCESDK_LIB_DIR ${SOURCESDK_DIR}/lib)

if(WINDOWS)
	set(SOURCESDK_LIB_PLATFORM_DIR "${SOURCESDK_LIB_DIR}/public/win64")

	set(SOURCESDK_LINK_LIBRARIES
		${SOURCESDK_LINK_LIBRARIES}

		${SOURCESDK_LIB_PLATFORM_DIR}/tier0.lib
		# ${SOURCESDK_LIB_PLATFORM_DIR}/tier1.lib
		# ${SOURCESDK_LIB_PLATFORM_DIR}/interfaces.lib
		# ${SOURCESDK_LIB_PLATFORM_DIR}/mathlib.lib
	)
elseif(LINUX)
	set(SOURCESDK_LIB_PLATFORM_DIR "${SOURCESDK_LIB_DIR}/linux64")

	set(SOURCESDK_LINK_LIBRARIES
		${SOURCESDK_LINK_LIBRARIES}

		${SOURCESDK_LIB_PLATFORM_DIR}/libtier0.so
		# ${SOURCESDK_LIB_PLATFORM_DIR}/tier1.a
		# ${SOURCESDK_LIB_PLATFORM_DIR}/interfaces.a
		# ${SOURCESDK_LIB_PLATFORM_DIR}/mathlib.a
	)
else()
	message(FATAL_ERROR "Unsupported platform")
endif()
