#include <logger/message.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/strtools.h>

LoggingResponse_t CLoggingMessage::MessageFormat(const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Message(sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormat(Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Message(aColor, sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormatLn(const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Message(sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormatLn(Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Message(aColor, sBuffer);
}

CLoggerScope CLoggingMessage::CreateMessagesScope(const char *pszStartWith, const char *pszEnd) const
{
#ifdef DEBUG
	CBufferStringLog sStartWith(LOGGER_FORMAT_MESSAGE_STARTWITH);

	sStartWith.Append(pszStartWith, -1);

	return CLoggerScope(LOGGER_COLOR_MESSAGE, sStartWith.String(), pszEnd);
#else
	return CLoggerScope(LOGGER_COLOR_MESSAGE, pszStartWith, pszEnd);
#endif
}
