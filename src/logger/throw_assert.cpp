#include <logger/throw_assert.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/strtools.h>

LoggingResponse_t CLoggingThrowAssert::ThrowAssertFormat(const LeafCodeInfo_t &aCode, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return ThrowAssert(aCode, sBuffer);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssertFormat(const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return ThrowAssert(aCode, aColor, sBuffer);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssertFormatLn(const LeafCodeInfo_t &aCode, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return ThrowAssert(aCode, sBuffer);
}

LoggingResponse_t CLoggingThrowAssert::ThrowAssertFormatLn(const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);
	sBuffer += '\n';

	return ThrowAssert(aCode, aColor, sBuffer);
}

CLoggerScope CLoggingThrowAssert::CreateAssertScope(const char *pszStartWith, const char *pszEnd) const
{
#ifdef DEBUG
	CBufferStringLog sStartWith(LOGGER_FORMAT_ASSERT_STARTWITH);

	sStartWith.Append(pszStartWith, -1);

	return CLoggerScope(LOGGER_COLOR_ASSERT, sStartWith.String(), pszEnd);
#else
	return CLoggerScope(LOGGER_COLOR_ASSERT, pszStartWith, pszEnd);
#endif
}

