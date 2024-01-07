#ifndef _INCLUDE_LOGGER_ERROR_HPP_
#define _INCLUDE_LOGGER_ERROR_HPP_

#include "ilogging.hpp"

#define LOGGER_FORMAT_ERROR_STARTWITH "ERROR: "
#define LOGGER_FORMAT_ERROR_STARTWITH_PREIFIX "[%s] " LOGGER_FORMAT_ERROR_STARTWITH
#define LOGGER_FORMAT_ERROR LOGGER_FORMAT_ERROR_STARTWITH_PREIFIX "%s\n"
#define LOGGER_COLOR_ERROR {255, 0, 0, 255}

class CLoggingError : virtual protected ILogging
{
	using ThisClass = CLoggingError;

public:
	virtual LoggingResponse_t Error(const char *pszContent);
	virtual LoggingResponse_t Error(const Color &aColor, const char *pszContent);

	virtual LoggingResponse_t ErrorFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	virtual LoggingResponse_t ErrorFormat(const Color &aColor, const char *pszFormat, ...) FMTFUNCTION(3, 4);

protected:
	static const LoggingSeverity_t s_eSeverity = LS_ERROR;
};

#endif // _INCLUDE_LOGGER_ERROR_HPP_
