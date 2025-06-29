#ifndef _INCLUDE_LOGGER_THROW_ASSERT_HPP_
#define _INCLUDE_LOGGER_THROW_ASSERT_HPP_

#pragma once

#include "ilogging.hpp"
#include "scope.hpp"

#define LOGGER_FORMAT_ASSERT_STARTWITH "ASSERT: "
#define LOGGER_FORMAT_ASSERT_STARTWITH_PREIFIX "[%s] " LOGGER_FORMAT_ASSERT_STARTWITH
#define LOGGER_FORMAT_ASSERT LOGGER_FORMAT_ASSERT_STARTWITH_PREIFIX "%s\n"
#define LOGGER_COLOR_ASSERT Color(255, 127, 0, 255)

class CLoggingThrowAssert : virtual protected ILogging
{
protected:
	static const LoggingSeverity_t s_eSeverity = LS_ASSERT;

public:
	virtual LoggingResponse_t ThrowAssert(const LeafCodeInfo_t &aCode, const char *pszContent) const { return InternalMessage(s_eSeverity, aCode, pszContent); }
	virtual LoggingResponse_t ThrowAssert(const LeafCodeInfo_t &aCode, Color aColor, const char *pszContent) const { return InternalMessage(s_eSeverity, aCode, aColor, pszContent); }

	virtual LoggingResponse_t ThrowAssertFormat(const LeafCodeInfo_t &aCode, const char *pszFormat, ...) const FMTFUNCTION(3, 4);
	virtual LoggingResponse_t ThrowAssertFormat(const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...) const FMTFUNCTION(4, 5);

	virtual LoggingResponse_t ThrowAssertFormatLn(const LeafCodeInfo_t &aCode, const char *pszFormat, ...) const FMTFUNCTION(3, 4);
	virtual LoggingResponse_t ThrowAssertFormatLn(const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...) const FMTFUNCTION(4, 5);

public:
	virtual CLoggerScope CreateAssertScope(const char *pszStartWith = "", const char *pszEnd = "\n") const;
}; // CLoggingThrowAssert

#endif // _INCLUDE_LOGGER_THROW_ASSERT_HPP_
