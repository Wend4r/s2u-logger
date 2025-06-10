#include <logger/warning.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/strtools.h>

LoggingResponse_t CLoggingWarning::WarningFormat(const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Warning(sBuffer);
}

LoggingResponse_t CLoggingWarning::WarningFormat(Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Warning(aColor, sBuffer);
}

LoggingResponse_t CLoggingWarning::WarningFormatLn(const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Warning(sBuffer);
}

LoggingResponse_t CLoggingWarning::WarningFormatLn(Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Warning(aColor, sBuffer);
}

CLoggerScope CLoggingWarning::CreateWarningsScope(const char *pszStartWith, const char *pszEnd) const
{
#ifdef DEBUG
	CBufferStringLog sStartWith(LOGGER_FORMAT_WARNING_STARTWITH);

	sStartWith += pszStartWith;

	return CLoggerScope(LOGGER_COLOR_WARNING, sStartWith.String(), pszEnd);
#else
	return CLoggerScope(LOGGER_COLOR_WARNING, pszStartWith, pszEnd);
#endif
}
