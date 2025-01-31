#ifndef _INCLUDE_LOGGER_WARNING_HPP_
#define _INCLUDE_LOGGER_WARNING_HPP_

#include "ilogging.hpp"
#include "scope.hpp"

#define LOGGER_FORMAT_WARNING_STARTWITH "WARNING: "
#define LOGGER_FORMAT_WARNING_STARTWITH_PREIFIX "[%s] " LOGGER_FORMAT_WARNING_STARTWITH
#define LOGGER_FORMAT_WARNING LOGGER_FORMAT_WARNING_STARTWITH_PREIFIX "%s\n"
#define LOGGER_COLOR_WARNING {255, 255, 0, 255}

class CLoggingWarning : virtual protected ILogging
{
	using This = CLoggingWarning;

public:
	virtual LoggingResponse_t Warning(const CUtlString &sContent);
	virtual LoggingResponse_t Warning(Color aColor, const CUtlString &sContent);

	virtual LoggingResponse_t WarningFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	virtual LoggingResponse_t WarningFormat(Color aColor, const char *pszFormat, ...) FMTFUNCTION(3, 4);

	virtual LoggingResponse_t WarningFormatLn(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	virtual LoggingResponse_t WarningFormatLn(Color aColor, const char *pszFormat, ...) FMTFUNCTION(3, 4);

public:
	virtual CLoggerScope CreateWarningsScope(const CUtlString &sStartWith = "", const CUtlString &sEnd = "\n");

protected:
	static const LoggingSeverity_t s_eSeverity = LS_WARNING;
}; // CLoggingWarning

#endif // _INCLUDE_LOGGER_WARNING_HPP_
