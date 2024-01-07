#include "warning.hpp"

#include <tier0/strtools.h>

LoggingResponse_t CLoggingWarning::Warning(const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingWarning::Warning(const Color &aColor, const char *pszContent)
{
	return this->InternalMessage(ThisClass::s_eSeverity, aColor, pszContent);
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