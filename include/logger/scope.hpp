#ifndef _INCLUDE_LOGGER_SCOPE_HPP_
#define _INCLUDE_LOGGER_SCOPE_HPP_

#pragma once

#include <functional>

#include <color.h>
#include <tier0/bufferstring.h>
#include <tier0/platform.h>
#include <tier0/utlstring.h>
#include <tier1/utlvector.h>

struct ScopeMessage_t
{
	Color color;
	CUtlString content;
}; // ScopeMessage_t

class CLoggerScope : public CUtlVectorBase<ScopeMessage_t>
{
	using This = CLoggerScope;

public:
	using SendFunc_t = std::function<void (const char *)>;
	using SendColorFunc_t = std::function<void (Color, const char *)>;

	CLoggerScope(Color rgba, const char *pszStartWith = "", const char *pszEnd = "\n")
	 :  m_color(rgba), 
	    m_sStartsWith(pszStartWith), 
	    m_sEnds(pszEnd)
	{
	}

	CLoggerScope &operator+=(const CLoggerScope &other) { AppendFrom(other); }

	Color GetColor() const                      { return m_color; }
	void SetColor(Color rgbaNew)                { m_color = rgbaNew; }
	const CBufferString &GetStartsWith() const  { return m_sStartsWith; }
	const CBufferString &GetEnds() const        { return m_sEnds; }

	int Push(const char *pszContent)                { return AddToTail(ScopeMessage_t{m_color, pszContent}); }
	int Push(Color rgba, const char *pszContent)    { return AddToTail(ScopeMessage_t{rgba, pszContent}); }

	int PushFormat(const char *pszFormat, ...) FMTFUNCTION(2, 3);
	int PushFormat(Color rgba, const char *pszFormat, ...) FMTFUNCTION(3, 4);

	int Send(const SendFunc_t &funcOn) const;
	int SendColor(const SendColorFunc_t &funcOn) const;

	CLoggerScope &AppendFrom(const CLoggerScope &other)
	{
		EnsureCapacity(other.Count());
		other.SendColor([&](Color rgba, const char *pszConent) { Push(rgba, pszConent); });

		return *this;
	}

private:
	Color m_color;
	CBufferString m_sStartsWith;
	CBufferString m_sEnds;
}; // CLoggerScope

#endif // _INCLUDE_LOGGER_SCOPE_HPP_
