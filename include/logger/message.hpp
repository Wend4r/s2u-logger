#ifndef _INCLUDE_LOGGER_MESSAGE_HPP_
#define _INCLUDE_LOGGER_MESSAGE_HPP_

#pragma once

#include "ilogging.hpp"
#include "scope.hpp"

#define LOGGER_FORMAT_MESSAGE_STARTWITH ""
#define LOGGER_FORMAT_MESSAGE_STARTWITH_PREFIX "[%s] " LOGGER_FORMAT_MESSAGE_STARTWITH
#define LOGGER_FORMAT_MESSAGE LOGGER_FORMAT_MESSAGE_STARTWITH_PREFIX "%s\n"
#define LOGGER_COLOR_MESSAGE Color(255, 255, 255, 255)

class CLoggingMessage : virtual protected ILogging
{
protected:
	static const LoggingSeverity_t s_eSeverity = LS_MESSAGE;

public:
	virtual LoggingResponse_t Message(const char *pszContent) const { return InternalMessage(s_eSeverity, pszContent); }
	virtual LoggingResponse_t Message(Color aColor, const char *pszContent) const { return InternalMessage(s_eSeverity, aColor, pszContent); }

	virtual LoggingResponse_t MessageFormat(const char *pszFormat, ...) const FMTFUNCTION(2, 3);
	virtual LoggingResponse_t MessageFormat(Color aColor, const char *pszFormat, ...) const FMTFUNCTION(3, 4);

	virtual LoggingResponse_t MessageFormatLn(const char *pszFormat, ...) const FMTFUNCTION(2, 3);
	virtual LoggingResponse_t MessageFormatLn(Color aColor, const char *pszFormat, ...) const FMTFUNCTION(3, 4);

public:
	virtual CLoggerScope CreateMessagesScope(const char *pszStartWith = "", const char *pszEnd = "\n") const;
}; // CLoggingMessage

#endif // _INCLUDE_LOGGER_MESSAGE_HPP_
