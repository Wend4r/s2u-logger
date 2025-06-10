#ifndef _INCLUDE_LOGGER_DETAILED_HPP_
#define _INCLUDE_LOGGER_DETAILED_HPP_

#pragma once

#include "ilogging.hpp"
#include "scope.hpp"

#define LOGGER_FORMAT_DETAILED_STARTWITH "DEV: "
#define LOGGER_FORMAT_DETAILED_STARTWITH_PREFIX "[%s] " LOGGER_FORMAT_DETAILED_STARTWITH_ADDITIONAL
#define LOGGER_FORMAT_DETAILED LOGGER_FORMAT_DETAILED_STARTWITH_PREFIX "%s\n"
#define LOGGER_COLOR_DETAILED Color(255, 255, 255, 191)

class CLoggingDetailed : virtual protected ILogging
{
protected:
	static const LoggingSeverity_t s_eSeverity = LS_DETAILED;

public:
	virtual LoggingResponse_t Detailed(const char *pszContent) const { return InternalMessage(s_eSeverity, pszContent); }
	virtual LoggingResponse_t Detailed(Color aColor, const char *pszContent) const { return InternalMessage(s_eSeverity, aColor, pszContent); }

	virtual LoggingResponse_t DetailedFormat(const char *pszFormat, ...) const FMTFUNCTION(2, 3);
	virtual LoggingResponse_t DetailedFormat(Color aColor, const char *pszFormat, ...) const FMTFUNCTION(3, 4);

	virtual LoggingResponse_t DetailedFormatLn(const char *pszFormat, ...) const FMTFUNCTION(2, 3);
	virtual LoggingResponse_t DetailedFormatLn(Color aColor, const char *pszFormat, ...) const FMTFUNCTION(3, 4);

public:
	virtual CLoggerScope CreateDetailsScope(const char *pszStartWith = "", const char *pszEnd = "\n") const;
}; // CLoggingDetailed

#endif // _INCLUDE_LOGGER_DETAILED_HPP_
