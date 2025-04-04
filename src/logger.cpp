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

CLogger::CLogger(const char *pszName, RegisterTagsFunc pfnRegisterTagsFunc, int iFlags, LoggingVerbosity_t eVerbosity, Color aDefault)
{
	m_nChannelID = LoggingSystem_RegisterLoggingChannel(pszName, pfnRegisterTagsFunc, iFlags, eVerbosity, aDefault);
}

bool CLogger::IsChannelEnabled(LoggingSeverity_t eSeverity) const
{
	return LoggingSystem_IsChannelEnabled(m_nChannelID, eSeverity);
}

bool CLogger::IsChannelEnabled(LoggingVerbosity_t eVerbosity) const
{
	return LoggingSystem_IsChannelEnabled(m_nChannelID, eVerbosity);
}

LoggingVerbosity_t CLogger::GetChannelVerbosity() const
{
	return LoggingSystem_GetChannelVerbosity(m_nChannelID);
}

Color CLogger::GetColor() const
{
	Color rgba;

	rgba.SetRawColor(LoggingSystem_GetChannelColor(m_nChannelID));

	return rgba;
}

LoggingChannelFlags_t CLogger::GetFlags() const
{
	return LoggingSystem_GetChannelFlags(m_nChannelID);
}

LoggingResponse_t CLogger::InternalMessage(LoggingSeverity_t eSeverity, const char *pszContent) const
{
	return LoggingSystem_LogDirect(m_nChannelID, eSeverity, pszContent);
}

LoggingResponse_t CLogger::InternalMessage(LoggingSeverity_t eSeverity, Color aColor, const char *pszContent) const
{
	return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aColor, pszContent);
}

LoggingResponse_t CLogger::InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszContent) const
{
	return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aCode, pszContent);
}

LoggingResponse_t CLogger::InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszContent) const
{
	return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aCode, aColor, pszContent);
}

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
