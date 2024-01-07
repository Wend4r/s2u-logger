#ifndef _INCLUDE_LOGGER_ILOGGING_HPP_
#define _INCLUDE_LOGGER_ILOGGING_HPP_

#include <tier0/logging.h>

class ILogging
{
protected:
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const char *pszContent) = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const Color &aColor, const char *pszContent) = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszContent) = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszContent) = 0;

	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...) = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const Color &aColor, const char *pszFormat, ...) = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...) = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszFormat, ...) = 0;
};

#endif // _INCLUDE_LOGGER_ILOGGING_HPP_
