/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * Logger util for Source2 games.
 * Written by Wend4r (2023).
 * ======================================================
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

protected:
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const char *pszContent);
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const Color &aColor, const char *pszContent);
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszContent);
	LoggingResponse_t InternalMessage(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszContent);

	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const char *pszFormat, ...) override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const Color &aColor, const char *pszFormat, ...) override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const char *pszFormat, ...) override;
	LoggingResponse_t InternalMessageFormat(LoggingSeverity_t eSeverity, const LeafCodeInfo_t &aCode, const Color &aColor, const char *pszFormat, ...) override;

	void DoTests();

public:
	class Scope
	{
	public:
		typedef std::function<void (const char *)> SendFunc;
		typedef std::function<void (const Color &, const char *)> SendColorFunc;

		Scope(const Color &rgbaInit, const char *pszStartWith = "", const char *pszEnd = "\n");

		Scope &operator+=(const Scope &);

		const Color &GetColor() const;
		const char *GetStartWith() const;
		const char *GetEnd() const;
		size_t Count() const;

		void SetColor(const Color &rgba);

		size_t Push(const char *pszContent);
		size_t Push(const Color &rgba, const char *pszContent);

		size_t PushFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
		size_t PushFormat(const Color &rgba, const char *pszFormat, ...) FMTFUNCTION(3, 4);

		size_t Send(SendFunc funcOn);
		size_t SendColor(SendColorFunc funcOn);

		class Message
		{
		public:
			Message(const Color &rgbaInit, const char *pszContent = "");

			const Color &GetColor() const;
			const std::string &Get() const;
			size_t SetWithCopy(const char *pszContent);

		private:
			Color m_aColor;
			std::string m_sContent;
		};

	private:
		char m_sFormatBuffer[MAX_LOGGING_MESSAGE_LENGTH];

		Color m_aColor;

		std::string m_aStartWith;
		std::vector<Message> m_vec;
		std::string m_aEnd;
	};

	Scope CreateDetailsScope(const char *pszStartWith = "", const char *pszEnd = "\n");
	Scope CreateMessagesScope(const char *pszStartWith = "", const char *pszEnd = "\n");
	Scope CreateWarningsScope(const char *pszStartWith = "", const char *pszEnd = "\n");
	Scope CreateAssertScope(const char *pszStartWith = "", const char *pszEnd = "\n");
	Scope CreateErrorsScope(const char *pszStartWith = "", const char *pszEnd = "\n");

private:
	LoggingChannelID_t m_nChannelID;
};

#endif // _INCLUDE_LOGGER_HPP_
