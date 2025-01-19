#include <logger/message.hpp>

#include <stdarg.h>

#include <tier0/strtools.h>

LoggingResponse_t CLoggingMessage::Message(const CUtlString &sContent)
{
	return InternalMessage(This::s_eSeverity, sContent);
}

LoggingResponse_t CLoggingMessage::Message(Color aColor, const CUtlString &sContent)
{
	return InternalMessage(This::s_eSeverity, aColor, sContent);
}

LoggingResponse_t CLoggingMessage::MessageFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return Message(sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormat(Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return Message(aColor, sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormatLn(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	int nLength = V_vsnprintf((char *)sBuffer, sizeof(sBuffer) - 1, pszFormat, aParams);
	va_end(aParams);

	sBuffer[nLength++] = '\n';
	sBuffer[nLength++] = '\0';

	return Message(sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormatLn(Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	int nLength = V_vsnprintf((char *)sBuffer, sizeof(sBuffer) - 1, pszFormat, aParams);
	va_end(aParams);

	sBuffer[nLength++] = '\n';
	sBuffer[nLength++] = '\0';

	return Message(aColor, sBuffer);
}

CLoggerScope CLoggingMessage::CreateMessagesScope(const CUtlString &sStartWith, const CUtlString &sEnd)
{
#ifdef DEBUG
	char sDebugWith[32];

	char *pDebugWithResult = (char *)sDebugWith;

	V_strncpy(pDebugWithResult, LOGGER_FORMAT_MESSAGE_STARTWITH, sizeof(sDebugWith));

	int nResultSize = V_strlen(pDebugWithResult);

	V_strncpy(&pDebugWithResult[nResultSize], sStartWith, (int)(sizeof(sDebugWith) - nResultSize));

	return {LOGGER_COLOR_MESSAGE, pDebugWithResult, sEnd};
#else
	return {LOGGER_COLOR_MESSAGE, sStartWith, sEnd};
#endif
}
