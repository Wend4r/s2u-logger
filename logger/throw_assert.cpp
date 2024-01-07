#include "throw_assert.hpp"

#include <tier0/strtools.h>

LoggingResponse_t CLoggingThrowAssert::ThrowAssert(const LeafCodeInfo_t &aCode, const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, aCode, pszContent);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssert(const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, aCode, aColor, pszContent);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssertFormat(const LeafCodeInfo_t &aCode, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->ThrowAssert(aCode, (const char *)sBuffer);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssertFormat(const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return this->ThrowAssert(aCode, aColor, (const char *)sBuffer);
}