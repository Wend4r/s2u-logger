#include <logger/scope.hpp>

#include <stdarg.h>

#include <tier0/logging.h>
#include <tier0/strtools.h>

LoggerScope::LoggerScope(Color rgba, CUtlString sStartWith, CUtlString sEnd)
{
	this->m_aColor = rgba;

	this->m_sStartWith = sStartWith;
	this->m_aEnd = sEnd;
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
						sResultContent += this->m_sStartWith;
					}

					sResultContent += aTarget.m_sStartWith + aMsg.Get();
				}
				else
				{
					this->Push(rgbaSave, sResultContent);

					if(n)
					{
						sResultContent += this->m_sStartWith;
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
			this->Push(rgbaSave, sResultContent);
		}
	}

	return *this;
}

Color LoggerScope::GetColor() const
{
	return this->m_aColor;
}

CUtlString LoggerScope::GetStartWith() const
{
	return this->m_sStartWith;
}

CUtlString LoggerScope::GetEnd() const
{
	return this->m_aEnd;
}

int LoggerScope::Count() const
{
	return this->m_vec.Count();
}

void LoggerScope::SetColor(Color rgba)
{
	this->m_aColor = rgba;
}

int LoggerScope::Push(CUtlString sContent)
{
	Message aMsg(this->m_aColor);

	int nStoredLength = aMsg.SetWithCopy(sContent);

	this->m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int LoggerScope::Push(Color rgba, CUtlString sContent)
{
	Message aMsg(rgba);

	int nStoredLength = aMsg.SetWithCopy(sContent);

	this->m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int LoggerScope::PushFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	Message aMsg(this->m_aColor);

	int nStoredLength = aMsg.SetWithCopy(sBuffer);

	this->m_vec.AddToTail(aMsg);

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

	this->m_vec.AddToTail(aMsg);

	return nStoredLength;
}

int LoggerScope::Send(SendFunc funcOn)
{
	CUtlString sResultContent;

	int nSize = this->m_vec.Count();
	
	for(int n = 0; n < nSize; n++)
	{
		sResultContent += this->m_sStartWith + this->m_vec[n].Get() + this->m_aEnd;
	}

	funcOn(sResultContent);

	return nSize;
}

int LoggerScope::SendColor(SendColorFunc funcOn)
{
	CUtlString sResultContent;

	int nSize = this->m_vec.Count();

	Color rgbaSave = this->m_aColor;

	for(int n = 0; n < nSize; n++)
	{
		const auto &aMsg = this->m_vec[n];

		if(aMsg.GetColor() == rgbaSave)
		{
			sResultContent += this->m_sStartWith + aMsg.Get() + this->m_aEnd;
		}
		else
		{
			funcOn(rgbaSave, sResultContent);

			sResultContent = this->m_sStartWith + aMsg.Get() + this->m_aEnd;
			rgbaSave = aMsg.GetColor();
		}
	}

	if(!sResultContent.IsEmpty())
	{
		funcOn(rgbaSave, sResultContent);
	}

	return nSize;
}

LoggerScope::Message::Message(Color rgbaInit, CUtlString sContent)
 :  m_aColor(rgbaInit),
    m_sContent(sContent)
{
}

Color LoggerScope::Message::GetColor() const
{
	return this->m_aColor;
}

CUtlString LoggerScope::Message::Get() const
{
	return this->m_sContent;
}

int LoggerScope::Message::SetWithCopy(CUtlString sContent)
{
	this->m_sContent = sContent;

	return this->m_sContent.Length();
}