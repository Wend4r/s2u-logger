#ifndef _INCLUDE_LOGGER_SCOPE_HPP_
#define _INCLUDE_LOGGER_SCOPE_HPP_

#include <functional>

#include <color.h>
#include <tier0/platform.h>
#include <tier0/utlstring.h>
#include <tier1/utlvector.h>

class LoggerScope
{
	using This = LoggerScope;

public:
	using SendFunc = std::function<void (CUtlString)>;
	using SendColorFunc = std::function<void (Color, CUtlString)>;

	LoggerScope(Color rgbaInit, CUtlString sStartWith = "", CUtlString sEnd = "\n");

	LoggerScope &operator+=(const LoggerScope &);

	Color GetColor() const;
	CUtlString GetStartWith() const;
	CUtlString GetEnd() const;
	int Count() const;

	void SetColor(Color rgba);

	int Push(CUtlString sContent);
	int Push(Color rgba, CUtlString sContent);

	int PushFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	int PushFormat(Color rgba, const char *pszFormat, ...) FMTFUNCTION(3, 4);

	int Send(SendFunc funcOn);
	int SendColor(SendColorFunc funcOn);

	class Message
	{
	public:
		Message(Color rgbaInit, CUtlString sContent = "");

		Color GetColor() const;
		CUtlString Get() const;
		int SetWithCopy(CUtlString sContent);

	private:
		Color m_aColor;
		CUtlString m_sContent;
	}; // LoggerScope::Message

private:
	Color m_aColor;

	CUtlString m_sStartWith;
	CUtlVector<Message> m_vec;
	CUtlString m_aEnd;
}; // LoggerScope

#endif // _INCLUDE_LOGGER_SCOPE_HPP_
