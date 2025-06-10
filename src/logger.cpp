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

#include <logger/macros.hpp>
#include <logger.hpp>

#include <tier0/bufferstring.h>

LoggingResponse_t CLogger::InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return InternalMessage(eSeverity, sBuffer);
}

LoggingResponse_t CLogger::InternalMessageFormat(LoggingSeverity_t eSeverity, Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return InternalMessage(eSeverity, aColor, sBuffer);
}

LoggingResponse_t CLogger::InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return InternalMessage(eSeverity, sBuffer);
}

LoggingResponse_t CLogger::InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...) const
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return InternalMessage(eSeverity, aColor, sBuffer);
}

void CLogger::DoTests() const
{ 
	DetailedFormat("LS_DETAILED = %d\n", LS_DETAILED);
	MessageFormat("LS_MESSAGE = %d\n", LS_MESSAGE);
	WarningFormat("LS_WARNING = %d\n", LS_WARNING);
	ThrowAssertFormat({__FILE__, __LINE__, __FUNCTION__}, "LS_ASSERT = %d\n", LS_ASSERT);
	ErrorFormat("LS_ERROR = %d\n", LS_ERROR);
}
