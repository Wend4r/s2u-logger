#include <logger/scope.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/logging.h>
#include <tier0/strtools.h>

int CLoggerScope::PushFormat(const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return AddToTail(ScopeMessage_t{m_color, sBuffer.String()});
}

int CLoggerScope::PushFormat(Color rgba, const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	return AddToTail(ScopeMessage_t{rgba, sBuffer.String()});
}

int CLoggerScope::Send(const SendFunc_t &funcOn) const
{
	CBufferStringLog sResult;

	for(const auto &msg : *this)
	{
		sResult.Append(m_sStartsWith);
		sResult.Append(msg.content);
		sResult.Append(m_sEnds);
	}

	funcOn(sResult.String());

	return Count();
}

int CLoggerScope::SendColor(const SendColorFunc_t &funcOn) const
{
	CBufferStringLog sResult;

	Color rgbaCurrent = m_color;

	for(const auto &msg : *this)
	{
		if(msg.color == rgbaCurrent)
		{
			sResult.Append(m_sStartsWith);
			sResult.Append(msg.content);
			sResult.Append(m_sEnds);
		}
		else
		{
			funcOn(rgbaCurrent, sResult.String());

			sResult.Clear();
			sResult.Set(m_sStartsWith);
			sResult.Append(msg.content);
			sResult.Append(m_sEnds);
			rgbaCurrent = msg.color;
		}
	}

	if(!sResult.IsEmpty())
	{
		funcOn(rgbaCurrent, sResult);
	}

	return Count();
}
