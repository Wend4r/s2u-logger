#ifndef _INCLUDE_LOGGER_SCOPE_HPP_
#define _INCLUDE_LOGGER_SCOPE_HPP_

#include <functional>

#include <color.h>
#include <tier0/platform.h>
#include <tier0/utlstring.h>
#include <tier1/utlvector.h>

class CLoggerScope
{
	using This = CLoggerScope;

public:
	using SendFunc_t = std::function<void (const CUtlString &)>;
	using SendColorFunc_t = std::function<void (Color, const CUtlString &)>;

	CLoggerScope(Color rgbaInit, const CUtlString &sStartWith = "", const CUtlString &sEnd = "\n");

	CLoggerScope &operator+=(const CLoggerScope &);

	Color GetColor() const;
	const CUtlString &GetStartWith() const;
	const CUtlString &GetEnd() const;
	int Count() const;

	void SetColor(Color rgba);

	int Push(const CUtlString &sContent);
	int Push(Color rgba, const CUtlString &sContent);

	int PushFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	int PushFormat(Color rgba, const char *pszFormat, ...) FMTFUNCTION(3, 4);

	int Send(const SendFunc_t &funcOn);
	int SendColor(const SendColorFunc_t &funcOn);

	class Message_t
	{
	public:
		Message_t(Color rgbaInit, const CUtlString &sContent = "");

		Color GetColor() const;
		const CUtlString &Get() const;
		int SetWithCopy(const CUtlString &sContent);

	private:
		Color m_aColor;
		CUtlString m_sContent;
	}; // CLoggerScope::Message_t

private:
	Color m_aColor;

	CUtlString m_sStartWith;
	CUtlVector<Message_t> m_vec;
	CUtlString m_aEnd;
}; // CLoggerScope

#endif // _INCLUDE_LOGGER_SCOPE_HPP_
