#ifndef _INCLUDE_LOGGER_WARNING_HPP_
#define _INCLUDE_LOGGER_WARNING_HPP_

#include "ilogging.hpp"
#include "scope.hpp"

#define LOGGER_FORMAT_WARNING_STARTWITH "WARNING: "
#define LOGGER_FORMAT_WARNING_STARTWITH_PREIFIX "[%s] " LOGGER_FORMAT_WARNING_STARTWITH
#define LOGGER_FORMAT_WARNING LOGGER_FORMAT_WARNING_STARTWITH_PREIFIX "%s\n"
#define LOGGER_COLOR_WARNING Color(255, 255, 0, 255)

class CLoggingWarning : virtual protected ILogging
{
protected:
	static const LoggingSeverity_t s_eSeverity = LS_WARNING;

public:
	virtual LoggingResponse_t Warning(const char *pszContent) const { return InternalMessage(s_eSeverity, pszContent); }
	virtual LoggingResponse_t Warning(Color aColor, const char *pszContent) const { return InternalMessage(s_eSeverity, aColor, pszContent); }

	virtual LoggingResponse_t WarningFormat(const char *pszFormat, ...) const FMTFUNCTION(2, 3);
	virtual LoggingResponse_t WarningFormat(Color aColor, const char *pszFormat, ...) const FMTFUNCTION(3, 4);

	virtual LoggingResponse_t WarningFormatLn(const char *pszFormat, ...) const FMTFUNCTION(2, 3);
	virtual LoggingResponse_t WarningFormatLn(Color aColor, const char *pszFormat, ...) const FMTFUNCTION(3, 4);

public:
	virtual CLoggerScope CreateWarningsScope(const char *pszStartWith = "", const char *pszEnd = "\n") const;
}; // CLoggingWarning

#endif // _INCLUDE_LOGGER_WARNING_HPP_
