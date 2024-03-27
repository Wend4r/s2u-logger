#include <logger/warning.hpp>

#include <stdarg.h>

#include <tier0/strtools.h>

LoggingResponse_t CLoggingWarning::Warning(const char *pszContent)
{
	return this->InternalMessage(This::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingWarning::Warning(const Color &aColor, const char *pszContent)
{
	return this->InternalMessage(This::s_eSeverity, aColor, pszContent);
}

LoggingResponse_t CLoggingWarning::WarningFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->Warning((const char *)sBuffer);
}

LoggingResponse_t CLoggingWarning::WarningFormat(const Color &aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->Warning(aColor, (const char *)sBuffer);
}

LoggerScope CLoggingWarning::CreateWarningsScope(const char *pszStartWith, const char *pszEnd)
{
#ifdef DEBUG
	char sDebugWith[32];

	char *pDebugWithResult = (char *)sDebugWith;

	V_strncpy(pDebugWithResult, LOGGER_FORMAT_WARNING_STARTWITH, sizeof(sDebugWith));

	size_t nResultSize = V_strlen(pDebugWithResult);

	V_strncpy(&pDebugWithResult[nResultSize], pszStartWith, (int)(sizeof(sDebugWith) - nResultSize));

	return {LOGGER_COLOR_WARNING, pDebugWithResult, pszEnd};
#else
	return {LOGGER_COLOR_WARNING, pszStartWith, pszEnd};
#endif
}
