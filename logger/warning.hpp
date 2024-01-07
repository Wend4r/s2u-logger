#ifndef _INCLUDE_LOGGER_WARNING_HPP_
#define _INCLUDE_LOGGER_WARNING_HPP_

#include "ilogging.hpp"

#define LOGGER_FORMAT_WARNING_STARTWITH "WARNING: "
#define LOGGER_FORMAT_WARNING_STARTWITH_PREIFIX "[%s] " LOGGER_FORMAT_WARNING_STARTWITH
#define LOGGER_FORMAT_WARNING LOGGER_FORMAT_WARNING_STARTWITH_PREIFIX "%s\n"
#define LOGGER_COLOR_WARNING {255, 255, 0, 255}

class CLoggingWarning : virtual protected ILogging
{
	using ThisClass = CLoggingWarning;

public:
	virtual LoggingResponse_t Warning(const char *pszContent);
	virtual LoggingResponse_t Warning(const Color &aColor, const char *pszContent);
	virtual LoggingResponse_t WarningFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	virtual LoggingResponse_t WarningFormat(const Color &aColor, const char *pszFormat, ...) FMTFUNCTION(3, 4);

protected:
	static const LoggingSeverity_t s_eSeverity = LS_WARNING;
};

#endif // _INCLUDE_LOGGER_WARNING_HPP_
