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

Logger::Logger(CUtlString sName, RegisterTagsFunc pfnRegisterTagsFunc, int iFlags, LoggingVerbosity_t eVerbosity, Color aDefault)
{
	this->m_nChannelID = LoggingSystem_RegisterLoggingChannel(sName, pfnRegisterTagsFunc, iFlags, eVerbosity, aDefault);
}

bool Logger::IsChannelEnabled(LoggingSeverity_t eSeverity)
{
	return LoggingSystem_IsChannelEnabled(this->m_nChannelID, eSeverity);
}

bool Logger::IsChannelEnabled(LoggingVerbosity_t eVerbosity)
{
	return LoggingSystem_IsChannelEnabled(this->m_nChannelID, eVerbosity);
}

LoggingVerbosity_t Logger::GetChannelVerbosity()
{
	return LoggingSystem_GetChannelVerbosity(this->m_nChannelID);
}

Color Logger::GetColor()
{
	Color rgba;

	rgba.SetRawColor(LoggingSystem_GetChannelColor(this->m_nChannelID));

	return rgba;
}

LoggingChannelFlags_t Logger::GetFlags()
{
	return LoggingSystem_GetChannelFlags(this->m_nChannelID);
}

LoggingResponse_t Logger::InternalMessage(LoggingSeverity_t eSeverity, CUtlString sContent)
{
	LoggingResponse_t eResponse = LR_ABORT;

	if(this->IsChannelEnabled(eSeverity))
	{
		eResponse = LoggingSystem_LogDirect(this->m_nChannelID, eSeverity, sContent);
	}

	return eResponse;
}

LoggingResponse_t Logger::InternalMessage(LoggingSeverity_t eSeverity, Color aColor, CUtlString sContent)
{
	LoggingResponse_t eResponse = LR_ABORT;

	if(this->IsChannelEnabled(eSeverity))
	{
		eResponse = LoggingSystem_LogDirect(this->m_nChannelID, eSeverity, aColor, sContent);
	}

	return eResponse;
}

LoggingResponse_t Logger::InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, CUtlString sContent)
{
	LoggingResponse_t eResponse = LR_ABORT;

	if(this->IsChannelEnabled(eSeverity))
	{
		eResponse = LoggingSystem_LogDirect(this->m_nChannelID, eSeverity, aCode, sContent);
	}

	return eResponse;
}

LoggingResponse_t Logger::InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, CUtlString sContent)
{
	LoggingResponse_t eResponse = LR_ABORT;

	if(this->IsChannelEnabled(eSeverity))
	{
		eResponse = LoggingSystem_LogDirect(this->m_nChannelID, eSeverity, aCode, aColor, sContent);
	}

	return eResponse;
}

LoggingResponse_t Logger::InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...)
{
	LoggingResponse_t eResponse = LR_ABORT;

	if(this->IsChannelEnabled(eSeverity))
	{
		char sBuffer[1024];

		va_list aParams;

		va_start(aParams, pszFormat);
		V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
		va_end(aParams);

		eResponse = this->InternalMessage(eSeverity, sBuffer);
	}

	return eResponse;
}

LoggingResponse_t Logger::InternalMessageFormat(LoggingSeverity_t eSeverity, Color aColor, const char *pszFormat, ...)
{
	LoggingResponse_t eResponse = LR_ABORT;

	if(this->IsChannelEnabled(eSeverity))
	{
		char sBuffer[1024];

		va_list aParams;

		va_start(aParams, pszFormat);
		V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
		va_end(aParams);

		eResponse = this->InternalMessage(eSeverity, aColor, sBuffer);
	}

	return eResponse;
}

LoggingResponse_t Logger::InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...)
{
	LoggingResponse_t eResponse = LR_ABORT;

	if(this->IsChannelEnabled(eSeverity))
	{
		char sBuffer[1024];

		va_list aParams;

		va_start(aParams, pszFormat);
		V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
		va_end(aParams);

		eResponse = this->InternalMessage(eSeverity, sBuffer);
	}

	return eResponse;
}

LoggingResponse_t Logger::InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, Color aColor, const char *pszFormat, ...)
{
	LoggingResponse_t eResponse = LR_ABORT;

	if(this->IsChannelEnabled(eSeverity))
	{
		char sBuffer[1024];

		va_list aParams;

		va_start(aParams, pszFormat);
		V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
		va_end(aParams);

		eResponse = this->InternalMessage(eSeverity, aColor, sBuffer);
	}

	return eResponse;
}

void Logger::DoTests()
{ 
	this->DetailedFormat("LS_DETAILED = %d\n", LS_DETAILED);
	this->MessageFormat("LS_MESSAGE = %d\n", LS_MESSAGE);
	this->WarningFormat("LS_WARNING = %d\n", LS_WARNING);
	this->ThrowAssertFormat({__FILE__, __LINE__, __FUNCTION__}, "LS_ASSERT = %d\n", LS_ASSERT);
	this->ErrorFormat("LS_ERROR = %d\n", LS_ERROR);
}
