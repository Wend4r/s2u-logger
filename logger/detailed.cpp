#include "detailed.hpp"

#include <tier0/strtools.h>

LoggingResponse_t CLoggingDetailed::Detailed(const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingDetailed::Detailed(const Color &aColor, const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, aColor, pszContent);
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
