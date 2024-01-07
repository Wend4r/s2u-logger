#ifndef _INCLUDE_LOGGER_DETAILED_HPP_
#define _INCLUDE_LOGGER_DETAILED_HPP_

#include "ilogging.hpp"

#define LOGGER_FORMAT_DETAILED_STARTWITH "DEV: "
#define LOGGER_FORMAT_DETAILED_STARTWITH_PREFIX "[%s] " LOGGER_FORMAT_DETAILED_STARTWITH_ADDITIONAL
#define LOGGER_FORMAT_DETAILED LOGGER_FORMAT_DETAILED_STARTWITH_PREFIX "%s\n"
#define LOGGER_COLOR_DETAILED {255, 255, 255, 191}

class CLoggingDetailed : virtual protected ILogging
{
	using ThisClass = CLoggingDetailed;

public:
	virtual LoggingResponse_t Detailed(const char *pszContent);
	virtual LoggingResponse_t Detailed(const Color &aColor, const char *pszContent);

	virtual LoggingResponse_t DetailedFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	virtual LoggingResponse_t DetailedFormat(const Color &aColor, const char *pszFormat, ...) FMTFUNCTION(3, 4);

protected:
	static const LoggingSeverity_t s_eSeverity = LS_DETAILED;
};

#endif // _INCLUDE_LOGGER_DETAILED_HPP_
