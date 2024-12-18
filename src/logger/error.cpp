#include <logger/error.hpp>

#include <stdarg.h>

#include <tier0/strtools.h>

LoggingResponse_t CLoggingError::Error(const CUtlString &sContent)
{
	return InternalMessage(This::s_eSeverity, sContent);
}

LoggingResponse_t CLoggingError::Error(Color aColor, const CUtlString &sContent)
{
	return InternalMessage(This::s_eSeverity, aColor, sContent);
}

LoggingResponse_t CLoggingError::ErrorFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return Error(sBuffer);
}

LoggingResponse_t CLoggingError::ErrorFormat(Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return Error(aColor, sBuffer);
}

LoggingResponse_t CLoggingError::ErrorFormatLn(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	int nLength = V_vsnprintf((char *)sBuffer, sizeof(sBuffer) - 1, pszFormat, aParams);
	va_end(aParams);

	sBuffer[nLength++] = '\n';
	sBuffer[nLength++] = '\0';

	return Error(sBuffer);
}

LoggingResponse_t CLoggingError::ErrorFormatLn(Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	int nLength = V_vsnprintf((char *)sBuffer, sizeof(sBuffer) - 1, pszFormat, aParams);
	va_end(aParams);

	sBuffer[nLength++] = '\n';
	sBuffer[nLength++] = '\0';

	return Error(aColor, sBuffer);
}

LoggerScope CLoggingError::CreateErrorsScope(const CUtlString &sStartWith, const CUtlString &sEnd)
{
#ifdef DEBUG
	char sDebugWith[32];

	char *pDebugWithResult = (char *)sDebugWith;

	V_strncpy(pDebugWithResult, LOGGER_FORMAT_ERROR_STARTWITH, sizeof(sDebugWith));

	int nResultSize = V_strlen(pDebugWithResult);

	V_strncpy(&pDebugWithResult[nResultSize], sStartWith, (int)(sizeof(sDebugWith) - nResultSize));

	return {LOGGER_COLOR_ERROR, pDebugWithResult, sEnd};
#else
	return {LOGGER_COLOR_ERROR, sStartWith, sEnd};
#endif
}
