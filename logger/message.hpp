#ifndef _INCLUDE_LOGGER_MESSAGE_HPP_
#define _INCLUDE_LOGGER_MESSAGE_HPP_

#include "ilogging.hpp"

#define LOGGER_FORMAT_MESSAGE_STARTWITH ""
#define LOGGER_FORMAT_MESSAGE_STARTWITH_PREFIX "[%s] " LOGGER_FORMAT_MESSAGE_STARTWITH
#define LOGGER_FORMAT_MESSAGE LOGGER_FORMAT_MESSAGE_STARTWITH_PREFIX "%s\n"
#define LOGGER_COLOR_MESSAGE {255, 255, 255, 255}

class CLoggingMessage : virtual protected ILogging
{
	using ThisClass = CLoggingMessage;

public:
	virtual LoggingResponse_t Message(const char *pszContent);
	virtual LoggingResponse_t Message(const Color &aColor, const char *pszContent);

	virtual LoggingResponse_t MessageFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	virtual LoggingResponse_t MessageFormat(const Color &aColor, const char *pszFormat, ...) FMTFUNCTION(3, 4);

protected:
	static const LoggingSeverity_t s_eSeverity = LS_MESSAGE;
};

#endif // _INCLUDE_LOGGER_MESSAGE_HPP_
