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

#include <logger.hpp>

CLogger::CLogger(const char *pszName, RegisterTagsFunc pfnRegisterTagsFunc, int iFlags, LoggingVerbosity_t eVerbosity, Color aDefault)
{
	m_nChannelID = LoggingSystem_RegisterLoggingChannel(pszName, pfnRegisterTagsFunc, iFlags, eVerbosity, aDefault);
}

bool CLogger::IsChannelEnabled(LoggingSeverity_t eSeverity)
{
	return LoggingSystem_IsChannelEnabled(m_nChannelID, eSeverity);
}

bool CLogger::IsChannelEnabled(LoggingVerbosity_t eVerbosity)
{
	return LoggingSystem_IsChannelEnabled(m_nChannelID, eVerbosity);
}

LoggingVerbosity_t CLogger::GetChannelVerbosity()
{
	return LoggingSystem_GetChannelVerbosity(m_nChannelID);
}

Color CLogger::GetColor()
{
	Color rgba;

	rgba.SetRawColor(LoggingSystem_GetChannelColor(m_nChannelID));

	return rgba;
}

LoggingChannelFlags_t CLogger::GetFlags()
{
	return LoggingSystem_GetChannelFlags(m_nChannelID);
}

LoggingResponse_t CLogger::InternalMessage(LoggingSeverity_t eSeverity, const char *pszContent)
{
	return LoggingSystem_LogDirect(m_nChannelID, eSeverity, pszContent);
}

LoggingResponse_t CLogger::InternalMessage(LoggingSeverity_t eSeverity, Color aColor, const char *pszContent)
{
	return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aColor, pszContent);
}

LoggingResponse_t CLogger::InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszContent)
{
	return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aCode, pszContent);
}

LoggingResponse_t CLogger::InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszContent)
{
	return LoggingSystem_LogDirect(m_nChannelID, eSeverity, aCode, aColor, pszContent);
}

LoggingResponse_t CLogger::InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...)
{
	char sBuffer[1024];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return InternalMessage(eSeverity, sBuffer);
}

LoggingResponse_t CLogger::InternalMessageFormat(LoggingSeverity_t eSeverity, Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return InternalMessage(eSeverity, aColor, sBuffer);
}

LoggingResponse_t CLogger::InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return InternalMessage(eSeverity, sBuffer);
}

LoggingResponse_t CLogger::InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	return InternalMessage(eSeverity, aColor, sBuffer);
}

void CLogger::DoTests()
{ 
	DetailedFormat("LS_DETAILED = %d\n", LS_DETAILED);
	MessageFormat("LS_MESSAGE = %d\n", LS_MESSAGE);
	WarningFormat("LS_WARNING = %d\n", LS_WARNING);
	ThrowAssertFormat({__FILE__, __LINE__, __FUNCTION__}, "LS_ASSERT = %d\n", LS_ASSERT);
	ErrorFormat("LS_ERROR = %d\n", LS_ERROR);
}
