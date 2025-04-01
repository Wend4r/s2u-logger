#include <logger/scope.hpp>
#include <logger/macros.hpp>

#include <stdarg.h>

#include <tier0/bufferstring.h>
#include <tier0/logging.h>
#include <tier0/strtools.h>

CLoggerScope::CLoggerScope(Color rgba, const char *pszStartWith, const char *pszEnd)
{
	m_aColor = rgba;

	m_sStartWith = pszStartWith;
	m_aEnd = pszEnd;
}

CLoggerScope &CLoggerScope::operator+=(const CLoggerScope &aTarget)
{
	if(aTarget.Count())
	{
		CUtlString sResultContent;

		int nSize = aTarget.m_vec.Count();

		Color rgbaSave = aTarget.m_aColor;

		{
			int n = 0;

			bool bNextIsColorCollide = aTarget.m_vec[0].GetColor() == rgbaSave;

			while(1)
			{
				const auto &aMsg = aTarget.m_vec[n];

				if(bNextIsColorCollide)
				{
					if(n)
					{
						sResultContent += m_sStartWith;
					}

					sResultContent += aTarget.m_sStartWith + aMsg.Get();
				}
				else
				{
					Push(rgbaSave, sResultContent);

					if(n)
					{
						sResultContent += m_sStartWith;
					}

					sResultContent = aTarget.m_sStartWith + aMsg.Get();
					rgbaSave = aMsg.GetColor();
				}

				n++;

				if(n < nSize)
				{
					bNextIsColorCollide = aTarget.m_vec[n].GetColor() == rgbaSave;

					if(bNextIsColorCollide)
					{
						sResultContent += aTarget.m_aEnd;
					}
				}
				else
				{
					break;
				}
			}
		}

		if(!sResultContent.IsEmpty())
		{
			Push(rgbaSave, sResultContent);
		}
	}

	return *this;
}

Color CLoggerScope::GetColor() const
{
	return m_aColor;
}

const CUtlString &CLoggerScope::GetStartWith() const
{
	return m_sStartWith;
}

const CUtlString &CLoggerScope::GetEnd() const
{
	return m_aEnd;
}

int CLoggerScope::Count() const
{
	return m_vec.Count();
}

void CLoggerScope::SetColor(Color rgba)
{
	m_aColor = rgba;
}

int CLoggerScope::Push(const char *pszContent)
{
	Message_t aMsg(m_aColor);

	int nStoredLength = aMsg.SetWithCopy(pszContent);

	m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int CLoggerScope::Push(Color rgba, const char *pszContent)
{
	Message_t aMsg(rgba);

	int nStoredLength = aMsg.SetWithCopy(pszContent);

	m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int CLoggerScope::PushFormat(const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	Message_t aMsg(m_aColor);

	int nStoredLength = aMsg.SetWithCopy(sBuffer);

	m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int CLoggerScope::PushFormat(Color rgba, const char *pszFormat, ...)
{
	CBufferStringLog sBuffer;

	LOGGER_APPEND_VA_TO_BUFFERSTRING(pszFormat, sBuffer);

	Message_t aMsg(rgba);

	int nStoredLength = aMsg.SetWithCopy(sBuffer);

	m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int CLoggerScope::Send(const SendFunc_t &funcOn)
{
	CUtlString sResultContent;

	int nSize = m_vec.Count();
	
	for(int n = 0; n < nSize; n++)
	{
		sResultContent += m_sStartWith + m_vec[n].Get() + m_aEnd;
	}

	funcOn(sResultContent);

	return nSize;
}

int CLoggerScope::SendColor(const SendColorFunc_t &funcOn)
{
	CUtlString sResultContent;

	int nSize = m_vec.Count();

	Color rgbaSave = m_aColor;

	for(int n = 0; n < nSize; n++)
	{
		const auto &aMsg = m_vec[n];

		if(aMsg.GetColor() == rgbaSave)
		{
			sResultContent += m_sStartWith + aMsg.Get() + m_aEnd;
		}
		else
		{
			funcOn(rgbaSave, sResultContent);

			sResultContent = m_sStartWith + aMsg.Get() + m_aEnd;
			rgbaSave = aMsg.GetColor();
		}
	}

	if(!sResultContent.IsEmpty())
	{
		funcOn(rgbaSave, sResultContent);
	}

	return nSize;
}

CLoggerScope::Message_t::Message_t(Color rgbaInit, const char *pszContent)
 :  m_aColor(rgbaInit),
    m_sContent(pszContent)
{
}

Color CLoggerScope::Message_t::GetColor() const
{
	return m_aColor;
}

const CUtlString &CLoggerScope::Message_t::Get() const
{
	return m_sContent;
}

int CLoggerScope::Message_t::SetWithCopy(const char *pszContent)
{
	m_sContent = pszContent;

	return m_sContent.Length();
}