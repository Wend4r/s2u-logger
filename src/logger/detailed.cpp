#include "detailed.hpp"

#include <stdarg.h>

#include <tier0/strtools.h>

LoggingResponse_t CLoggingDetailed::Detailed(const char *pszContent)
{
	return this->InternalMessage(This::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingDetailed::Detailed(const Color &aColor, const char *pszContent)
{
	return this->InternalMessage(This::s_eSeverity, aColor, pszContent);
}

LoggingResponse_t CLoggingDetailed::DetailedFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->Detailed((const char *)sBuffer);
}

LoggingResponse_t CLoggingDetailed::DetailedFormat(const Color &aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->Detailed(aColor, (const char *)sBuffer);
}

LoggerScope CLoggingDetailed::CreateDetailsScope(const char *pszStartWith, const char *pszEnd)
{
#ifdef DEBUG
	char sDebugWith[32];

	char *pDebugWithResult = (char *)sDebugWith;

	V_strncpy(pDebugWithResult, LOGGER_FORMAT_DETAILED_STARTWITH, sizeof(sDebugWith));

	size_t nResultSize = V_strlen(pDebugWithResult);

	V_strncpy(&pDebugWithResult[nResultSize], pszStartWith, (int)(sizeof(sDebugWith) - nResultSize));

	return {LOGGER_COLOR_DETAILED, pDebugWithResult, pszEnd};
#else
	return {LOGGER_COLOR_DETAILED, pszStartWith, pszEnd};
#endif
}
