#include "error.hpp"

#include <stdarg.h>

#include <tier0/strtools.h>

LoggingResponse_t CLoggingError::Error(const char *pszContent)
{
	return this->InternalMessage(This::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingError::Error(const Color &aColor, const char *pszContent)
{
	return this->InternalMessage(This::s_eSeverity, aColor, pszContent);
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

LoggerScope CLoggingError::CreateErrorsScope(const char *pszStartWith, const char *pszEnd)
{
#ifdef DEBUG
	char sDebugWith[32];

	char *pDebugWithResult = (char *)sDebugWith;

	V_strncpy(pDebugWithResult, LOGGER_FORMAT_ERROR_STARTWITH, sizeof(sDebugWith));

	size_t nResultSize = V_strlen(pDebugWithResult);

	V_strncpy(&pDebugWithResult[nResultSize], pszStartWith, (int)(sizeof(sDebugWith) - nResultSize));

	return {LOGGER_COLOR_ERROR, pDebugWithResult, pszEnd};
#else
	return {LOGGER_COLOR_ERROR, pszStartWith, pszEnd};
#endif
}
