#ifndef _INCLUDE_LOGGER_ILOGGING_HPP_
#define _INCLUDE_LOGGER_ILOGGING_HPP_

#pragma once

#include <stdarg.h>

#include <tier0/logging.h>
#include <tier0/utlstring.h>

class ILogging
{
protected:
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const char *pszContent) const = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, Color aColor, const char *pszContent) const = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszContent) const = 0;
	virtual LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszContent) const = 0;

	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...) const = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, Color aColor, const char *pszFormat, ...) const = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...) const = 0;
	virtual LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...) const = 0;
}; // ILogging

#endif // _INCLUDE_LOGGER_ILOGGING_HPP_
