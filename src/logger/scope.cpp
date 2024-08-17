#include <logger/scope.hpp>

#include <stdarg.h>

#include <tier0/logging.h>
#include <tier0/strtools.h>

LoggerScope::LoggerScope(Color rgba, const CUtlString &sStartWith, const CUtlString &sEnd)
{
	m_aColor = rgba;

	m_sStartWith = sStartWith;
	m_aEnd = sEnd;
}

LoggerScope &LoggerScope::operator+=(const LoggerScope &aTarget)
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

Color LoggerScope::GetColor() const
{
	return m_aColor;
}

const CUtlString &LoggerScope::GetStartWith() const
{
	return m_sStartWith;
}

const CUtlString &LoggerScope::GetEnd() const
{
	return m_aEnd;
}

int LoggerScope::Count() const
{
	return m_vec.Count();
}

void LoggerScope::SetColor(Color rgba)
{
	m_aColor = rgba;
}

int LoggerScope::Push(const CUtlString &sContent)
{
	Message aMsg(m_aColor);

	int nStoredLength = aMsg.SetWithCopy(sContent);

	m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int LoggerScope::Push(Color rgba, const CUtlString &sContent)
{
	Message aMsg(rgba);

	int nStoredLength = aMsg.SetWithCopy(sContent);

	m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int LoggerScope::PushFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	Message aMsg(m_aColor);

	int nStoredLength = aMsg.SetWithCopy(sBuffer);

	m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int LoggerScope::PushFormat(Color rgba, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	Message aMsg(rgba);

	int nStoredLength = aMsg.SetWithCopy(sBuffer);

	m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int LoggerScope::Send(const SendFunc &funcOn)
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

int LoggerScope::SendColor(const SendColorFunc &funcOn)
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

LoggerScope::Message::Message(Color rgbaInit, const CUtlString &sContent)
 :  m_aColor(rgbaInit),
    m_sContent(sContent)
{
}

Color LoggerScope::Message::GetColor() const
{
	return m_aColor;
}

const CUtlString &LoggerScope::Message::Get() const
{
	return m_sContent;
}

int LoggerScope::Message::SetWithCopy(const CUtlString &sContent)
{
	m_sContent = sContent;

	return m_sContent.Length();
}