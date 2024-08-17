#include <logger/detailed.hpp>

#include <stdarg.h>

#include <tier0/strtools.h>

LoggingResponse_t CLoggingDetailed::Detailed(const CUtlString &sContent)
{
	return InternalMessage(This::s_eSeverity, sContent);
}

LoggingResponse_t CLoggingDetailed::Detailed(Color aColor, const CUtlString &sContent)
{
	return InternalMessage(This::s_eSeverity, aColor, sContent);
}

LoggingResponse_t CLoggingDetailed::DetailedFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return Detailed(sBuffer);
}

LoggingResponse_t CLoggingDetailed::DetailedFormat(Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return Detailed(aColor, sBuffer);
}

LoggerScope CLoggingDetailed::CreateDetailsScope(const CUtlString &sStartWith, const CUtlString &sEnd)
{
#ifdef DEBUG
	char sDebugWith[32];

	char *pDebugWithResult = (char *)sDebugWith;

	V_strncpy(pDebugWithResult, LOGGER_FORMAT_DETAILED_STARTWITH, sizeof(sDebugWith));

	int nResultSize = V_strlen(pDebugWithResult);

	V_strncpy(&pDebugWithResult[nResultSize], sStartWith, (int)(sizeof(sDebugWith) - nResultSize));

	return {LOGGER_COLOR_DETAILED, pDebugWithResult, sEnd};
#else
	return {LOGGER_COLOR_DETAILED, sStartWith, sEnd};
#endif
}
