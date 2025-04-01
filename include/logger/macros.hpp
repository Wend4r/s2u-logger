#ifndef _INCLUDE_LOGGER_MACROS_HPP_
#define _INCLUDE_LOGGER_MACROS_HPP_

#pragma once

#include <tier0/bufferstring.h>

#define LOGGER_APPEND_VA_TO_BUFFERSTRING(formatVar, bufferVar) \
	{ \
		va_list vaParams; \
\
		va_start(vaParams, formatVar); \
		bufferVar.AppendFormatV(formatVar, vaParams); \
		va_end(vaParams); \
	}

using CBufferStringLog = CBufferStringN<MAX_LOGGING_MESSAGE_LENGTH>;

#endif // _INCLUDE_LOGGER_MACROS_HPP_
