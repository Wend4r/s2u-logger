#include "message.hpp"

#include <tier0/strtools.h>

LoggingResponse_t CLoggingMessage::Message(const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingMessage::Message(const Color &aColor, const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, aColor, pszContent);
}

LoggingResponse_t CLoggingMessage::MessageFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->Message((const char *)sBuffer);
}

LoggingResponse_t CLoggingMessage::MessageFormat(const Color &aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->Message(aColor, (const char *)sBuffer);
}