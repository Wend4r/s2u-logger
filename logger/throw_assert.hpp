#ifndef _INCLUDE_LOGGER_THROW_ASSERT_HPP_
#define _INCLUDE_LOGGER_THROW_ASSERT_HPP_

#include "ilogging.hpp"

#define LOGGER_FORMAT_ASSERT_STARTWITH "ASSERT: "
#define LOGGER_FORMAT_ASSERT_STARTWITH_PREIFIX "[%s] " LOGGER_FORMAT_ASSERT_STARTWITH
#define LOGGER_FORMAT_ASSERT LOGGER_FORMAT_ASSERT_STARTWITH_PREIFIX "%s\n"
#define LOGGER_COLOR_ASSERT {255, 127, 0, 255}

class CLoggingThrowAssert : virtual protected ILogging
{
	using ThisClass = CLoggingThrowAssert;

public:
	virtual LoggingResponse_t ThrowAssert(const LeafCodeInfo_t &aCode, const char *pszContent);
	virtual LoggingResponse_t ThrowAssert(const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszContent);

	virtual LoggingResponse_t ThrowAssertFormat(const LeafCodeInfo_t &aCode, const char *pszFormat, ...) FMTFUNCTION(3, 4);
	virtual LoggingResponse_t ThrowAssertFormat(const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszFormat, ...) FMTFUNCTION(4, 5);

protected:
	static const LoggingSeverity_t s_eSeverity = LS_ASSERT;
};

#endif // _INCLUDE_LOGGER_THROW_ASSERT_HPP_
