#include <logger/warning.hpp>

#include <stdarg.h>

#include <tier0/strtools.h>

LoggingResponse_t CLoggingWarning::Warning(CUtlString sContent)
{
	return InternalMessage(This::s_eSeverity, sContent);
}

LoggingResponse_t CLoggingWarning::Warning(Color aColor, CUtlString sContent)
{
	return InternalMessage(This::s_eSeverity, aColor, sContent);
}

LoggingResponse_t CLoggingWarning::WarningFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return Warning(sBuffer);
}

LoggingResponse_t CLoggingWarning::WarningFormat(Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return Warning(aColor, sBuffer);
}

LoggerScope CLoggingWarning::CreateWarningsScope(CUtlString sStartWith, CUtlString sEnd)
{
#ifdef DEBUG
	char sDebugWith[32];

	char *pDebugWithResult = (char *)sDebugWith;

	V_strncpy(pDebugWithResult, LOGGER_FORMAT_WARNING_STARTWITH, sizeof(sDebugWith));

	int nResultSize = V_strlen(pDebugWithResult);

	V_strncpy(&pDebugWithResult[nResultSize], sStartWith, (int)(sizeof(sDebugWith) - nResultSize));

	return {LOGGER_COLOR_WARNING, pDebugWithResult, sEnd};
#else
	return {LOGGER_COLOR_WARNING, sStartWith, sEnd};
#endif
}
