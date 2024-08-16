#ifndef _INCLUDE_LOGGER_ILOGGING_HPP_
#define _INCLUDE_LOGGER_ILOGGING_HPP_

#include <tier0/logging.h>
#include <tier0/utlstring.h>
#include <stdarg.h>

class ILogging
{
protected:
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, CUtlString sContent) = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, Color aColor, CUtlString sContent) = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, CUtlString sContent) = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, CUtlString sContent) = 0;

	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...) = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, Color aColor, const char *pszFormat, ...) = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...) = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...) = 0;
}; // ILogging

#endif // _INCLUDE_LOGGER_ILOGGING_HPP_
