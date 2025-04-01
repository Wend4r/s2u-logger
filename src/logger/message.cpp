#include <logger/message.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/strtools.h>

LoggingResponse_t CLoggingMessage::Message(const char *pszContent)
{
	return InternalMessage(This::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingMessage::Message(Color aColor, const char *pszContent)
{
	return InternalMessage(This::s_eSeverity, aColor, pszContent);
}

LoggingResponse_t CLoggingMessage::MessageFormat(const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Message(sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormat(Color aColor, const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Message(aColor, sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormatLn(const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Message(sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormatLn(Color aColor, const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Message(aColor, sBuffer);
}

CLoggerScope CLoggingMessage::CreateMessagesScope(const char *pszStartWith, const char *pszEnd)
{
#ifdef DEBUG
	CBufferStringLog sStartWith(LOGGER_FORMAT_MESSAGE_STARTWITH);

	sStartWith += pszStartWith;

	return {LOGGER_COLOR_MESSAGE, sStartWith, pszEnd};
#else
	return {LOGGER_COLOR_MESSAGE, pszStartWith, pszEnd};
#endif
}
