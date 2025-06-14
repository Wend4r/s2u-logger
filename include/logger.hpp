/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * Logger util for Source2 games.
 * Written by Wend4r (2023).
 * ======================================================

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _INCLUDE_LOGGER_HPP_
#define _INCLUDE_LOGGER_HPP_

#pragma once

#include <stddef.h>
#include <functional>
#include <string>

#include <tier0/dbg.h>
#include <tier0/logging.h>

#include "logger/detailed.hpp"
#include "logger/message.hpp"
#include "logger/warning.hpp"
#include "logger/throw_assert.hpp"
#include "logger/error.hpp"

class CLogger : public CLoggingDetailed, public CLoggingMessage, public CLoggingWarning, public CLoggingThrowAssert, public CLoggingError
{
public:
	CLogger(const char *pszName, RegisterTagsFunc pfnRegisterTagsFunc, int nFlags = 0, LoggingVerbosity_t eVerbosity = LV_DEFAULT, Color rgba = UNSPECIFIED_LOGGING_COLOR)
	 :  m_nChannelID(LoggingSystem_RegisterLoggingChannel(pszName, pfnRegisterTagsFunc, nFlags, eVerbosity, rgba))
	{
	}

public:
	bool IsChannelEnabled(LoggingSeverity_t eSeverity) const    { return LoggingSystem_IsChannelEnabled(m_nChannelID, eSeverity); }
	bool IsChannelEnabled(LoggingVerbosity_t eVerbosity) const  { return LoggingSystem_IsChannelEnabled(m_nChannelID, eVerbosity); }
	LoggingVerbosity_t GetChannelVerbosity() const              { return LoggingSystem_GetChannelVerbosity(m_nChannelID); }
	Color GetColor() const                                      { return LoggingSystem_GetChannelColor(m_nChannelID); }
	LoggingChannelFlags_t GetFlags() const                      { return LoggingSystem_GetChannelFlags(m_nChannelID); }

	// Bcompatibility.
	using Scope = CLoggerScope;

protected:
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const char *pszContent) const override { return LoggingSystem_LogDirect(m_nChannelID, eSeverity, pszContent); }
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, Color aColor, const char *pszContent) const override { return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aColor, pszContent); }
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszContent) const override { return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aCode, pszContent); }
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszContent) const override { return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aCode, aColor, pszContent); }

	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...) const override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, Color aColor, const char *pszFormat, ...) const override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...) const override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...) const override;

	void DoTests() const;

private:
	LoggingChannelID_t m_nChannelID;
}; // CLogger

class Logger final : public CLogger
{
public:
	using CBase = CLogger;
	using CBase::CBase;
}; // Logger

#endif // _INCLUDE_LOGGER_HPP_
