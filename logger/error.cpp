#include "error.hpp"

#include <tier0/strtools.h>

LoggingResponse_t CLoggingError::Error(const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingError::Error(const Color &aColor, const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, aColor, pszContent);
}

LoggingResponse_t CLoggingError::ErrorFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->Error((const char *)sBuffer);
}

LoggingResponse_t CLoggingError::ErrorFormat(const Color &aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->Error(aColor, (const char *)sBuffer);
}