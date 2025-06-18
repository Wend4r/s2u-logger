#include <logger/detailed.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/strtools.h>

LoggingResponse_t CLoggingDetailed::DetailedFormat(const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Detailed(sBuffer);
}

LoggingResponse_t CLoggingDetailed::DetailedFormat(Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Detailed(aColor, sBuffer);
}

LoggingResponse_t CLoggingDetailed::DetailedFormatLn(const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Detailed(sBuffer);
}

LoggingResponse_t CLoggingDetailed::DetailedFormatLn(Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Detailed(aColor, sBuffer);
}

CLoggerScope CLoggingDetailed::CreateDetailsScope(const char *pszStartWith, const char *pszEnd) const
{
#ifdef DEBUG
	CBufferStringLog sStartWith(LOGGER_FORMAT_DETAILED_STARTWITH);

	sStartWith.Append(pszStartWith, -1);

	return CLoggerScope(LOGGER_COLOR_DETAILED, sStartWith.String(), pszEnd);
#else
	return CLoggerScope(LOGGER_COLOR_DETAILED, pszStartWith, pszEnd);
#endif
}
