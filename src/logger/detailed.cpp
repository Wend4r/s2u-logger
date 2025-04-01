#include <logger/detailed.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/strtools.h>

LoggingResponse_t CLoggingDetailed::Detailed(const char *pszContent)
{
	return InternalMessage(This::s_eSeverity, pszContent);
}

LoggingResponse_t CLoggingDetailed::Detailed(Color aColor, const char *pszContent)
{
	return InternalMessage(This::s_eSeverity, aColor, pszContent);
}

LoggingResponse_t CLoggingDetailed::DetailedFormat(const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Detailed(sBuffer);
}

LoggingResponse_t CLoggingDetailed::DetailedFormat(Color aColor, const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Detailed(aColor, sBuffer);
}

LoggingResponse_t CLoggingDetailed::DetailedFormatLn(const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Detailed(sBuffer);
}

LoggingResponse_t CLoggingDetailed::DetailedFormatLn(Color aColor, const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Detailed(aColor, sBuffer);
}

CLoggerScope CLoggingDetailed::CreateDetailsScope(const char *pszStartWith, const char *pszEnd)
{
#ifdef DEBUG
	CBufferStringLog sStartWith(LOGGER_FORMAT_DETAILED_STARTWITH);

	sStartWith += pszStartWith;

	return {LOGGER_COLOR_DETAILED, sStartWith, pszEnd};
#else
	return {LOGGER_COLOR_DETAILED, pszStartWith, pszEnd};
#endif
}
