#ifndef _INCLUDE_LOGGER_ERROR_HPP_
#define _INCLUDE_LOGGER_ERROR_HPP_

#pragma once

#include "ilogging.hpp"
#include "scope.hpp"

#define LOGGER_FORMAT_ERROR_STARTWITH "ERROR: "
#define LOGGER_FORMAT_ERROR_STARTWITH_PREIFIX "[%s] " LOGGER_FORMAT_ERROR_STARTWITH
#define LOGGER_FORMAT_ERROR LOGGER_FORMAT_ERROR_STARTWITH_PREIFIX "%s\n"
#define LOGGER_COLOR_ERROR Color(255, 0, 0, 255)

class CLoggingError : virtual protected ILogging
{
protected:
	static const LoggingSeverity_t s_eSeverity = LS_ERROR;

public:
	virtual LoggingResponse_t Error(const char *pszContent) const { return InternalMessage(s_eSeverity, pszContent); }
	virtual LoggingResponse_t Error(Color aColor, const char *pszContent) const { return InternalMessage(s_eSeverity, aColor, pszContent); }

	virtual LoggingResponse_t ErrorFormat(const char *pszFormat, ...) const FMTFUNCTION(2, 3);
	virtual LoggingResponse_t ErrorFormat(Color aColor, const char *pszFormat, ...) const FMTFUNCTION(3, 4);

	virtual LoggingResponse_t ErrorFormatLn(const char *pszFormat, ...) const FMTFUNCTION(2, 3);
	virtual LoggingResponse_t ErrorFormatLn(Color aColor, const char *pszFormat, ...) const FMTFUNCTION(3, 4);

public:
	virtual CLoggerScope CreateErrorsScope(const char *pszStartWith = "", const char *pszEnd = "\n") const;
}; // CLoggingError

#endif // _INCLUDE_LOGGER_ERROR_HPP_
