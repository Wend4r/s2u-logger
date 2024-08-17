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
	using SendFunc = std::function<void (const CUtlString &)>;
	using SendColorFunc = std::function<void (Color, const CUtlString &)>;

	LoggerScope(Color rgbaInit, const CUtlString &sStartWith = "", const CUtlString &sEnd = "\n");

	LoggerScope &operator+=(const LoggerScope &);

	Color GetColor() const;
	const CUtlString &GetStartWith() const;
	const CUtlString &GetEnd() const;
	int Count() const;

	void SetColor(Color rgba);

	int Push(const CUtlString &sContent);
	int Push(Color rgba, const CUtlString &sContent);

	int PushFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	int PushFormat(Color rgba, const char *pszFormat, ...) FMTFUNCTION(3, 4);

	int Send(SendFunc funcOn);
	int SendColor(SendColorFunc funcOn);

	class Message
	{
	public:
		Message(Color rgbaInit, const CUtlString &sContent = "");

		Color GetColor() const;
		const CUtlString &Get() const;
		int SetWithCopy(const CUtlString &sContent);

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
