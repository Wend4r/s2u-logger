#include <logger/throw_assert.hpp>

#include <stdarg.h>

#include <tier0/strtools.h>

LoggingResponse_t CLoggingThrowAssert::ThrowAssert(const LeafCodeInfo_t &aCode, const CUtlString &sContent)
{
	return InternalMessage(This::s_eSeverity, aCode, sContent);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssert(const LeafCodeInfo_t &aCode, Color aColor, const CUtlString &sContent)
{
	return InternalMessage(This::s_eSeverity, aCode, aColor, sContent);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssertFormat(const LeafCodeInfo_t &aCode, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return ThrowAssert(aCode, sBuffer);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssertFormat(const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return ThrowAssert(aCode, aColor, sBuffer);
}

LoggerScope CLoggingThrowAssert::CreateAssertScope(const CUtlString &sStartWith, const CUtlString &sEnd)
{
#ifdef DEBUG
	char sDebugWith[32];

	char *pDebugWithResult = (char *)sDebugWith;

	V_strncpy(pDebugWithResult, LOGGER_FORMAT_ASSERT_STARTWITH, sizeof(sDebugWith));

	int nResultSize = V_strlen(pDebugWithResult);

	V_strncpy(&pDebugWithResult[nResultSize], sStartWith, (int)(sizeof(sDebugWith) - nResultSize));

	return {LOGGER_COLOR_ASSERT, pDebugWithResult, sEnd};
#else
	return {LOGGER_COLOR_ASSERT, sStartWith, sEnd};
#endif
}

