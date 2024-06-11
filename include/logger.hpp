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

class Logger : public CLoggingDetailed, public CLoggingMessage, public CLoggingWarning, public CLoggingThrowAssert, public CLoggingError
{
public:
	Logger(const char *pszName, RegisterTagsFunc pfnRegisterTagsFunc, int iFlags = 0, LoggingVerbosity_t eVerbosity = LV_DEFAULT, const Color &aDefault = UNSPECIFIED_LOGGING_COLOR);

public:
	bool IsChannelEnabled(LoggingSeverity_t eSeverity);
	bool IsChannelEnabled(LoggingVerbosity_t eVerbosity);
	LoggingVerbosity_t GetChannelVerbosity();
	Color GetColor();
	LoggingChannelFlags_t GetFlags();

	using Scope = LoggerScope;

protected:
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const char *pszContent) override;
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const Color &aColor, const char *pszContent) override;
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszContent) override;
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszContent) override;

	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...) override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const Color &aColor, const char *pszFormat, ...) override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...) override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszFormat, ...) override;

	void DoTests();

private:
	LoggingChannelID_t m_nChannelID;
}; // Logger

#endif // _INCLUDE_LOGGER_HPP_
