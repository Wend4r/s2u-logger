#include <logger/error.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/strtools.h>

LoggingResponse_t CLoggingError::ErrorFormat(const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Error(sBuffer);
}

LoggingResponse_t CLoggingError::ErrorFormat(Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return Error(aColor, sBuffer);
}

LoggingResponse_t CLoggingError::ErrorFormatLn(const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Error(sBuffer);
}

LoggingResponse_t CLoggingError::ErrorFormatLn(Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return Error(aColor, sBuffer);
}

CLoggerScope CLoggingError::CreateErrorsScope(const char *pszStartWith, const char *pszEnd) const
{
#ifdef DEBUG
	CBufferStringLog sStartWith(LOGGER_FORMAT_ERROR_STARTWITH);

	sStartWith += pszStartWith;

	return CLoggerScope(LOGGER_COLOR_ERROR, sStartWith.String(), pszEnd);
#else
	return CLoggerScope(LOGGER_COLOR_ERROR, pszStartWith, pszEnd);
#endif
}
