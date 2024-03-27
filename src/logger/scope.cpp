#include <logger/scope.hpp>

#include <stdarg.h>

#include <tier0/logging.h>
#include <tier0/strtools.h>

LoggerScope::LoggerScope(const Color &rgba, const char *pszStartWith, const char *pszEnd)
{
	this->m_aColor = rgba;

	this->m_aStartWith = pszStartWith;
	this->m_aEnd = pszEnd;
}

LoggerScope &LoggerScope::operator+=(const LoggerScope &aTarget)
{
	if(aTarget.Count())
	{
		std::string sResultContent;

		size_t nSize = aTarget.m_vec.size();

		Color rgbaSave = aTarget.m_aColor;

		{
			size_t n = 0;

			bool bNextIsColorCollide = aTarget.m_vec[0].GetColor() == rgbaSave;

			while(1)
			{
				const auto &aMsg = aTarget.m_vec[n];

				if(bNextIsColorCollide)
				{
					if(n)
					{
						sResultContent += this->m_aStartWith;
					}

					sResultContent += aTarget.m_aStartWith + aMsg.Get();
				}
				else
				{
					this->Push(rgbaSave, sResultContent.c_str());

					if(n)
					{
						sResultContent += this->m_aStartWith;
					}

					sResultContent = aTarget.m_aStartWith + aMsg.Get();
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

		if(sResultContent.size())
		{
			this->Push(rgbaSave, sResultContent.c_str());
		}
	}

	return *this;
}

const Color &LoggerScope::GetColor() const
{
	return this->m_aColor;
}

const char *LoggerScope::GetStartWith() const
{
	return this->m_aStartWith.c_str();
}

const char *LoggerScope::GetEnd() const
{
	return this->m_aEnd.c_str();
}

size_t LoggerScope::Count() const
{
	return this->m_vec.size();
}

void LoggerScope::SetColor(const Color &rgba)
{
	this->m_aColor = rgba;
}

size_t LoggerScope::Push(const char *pszContent)
{
	Message aMsg(this->m_aColor);

	size_t nStoredLength = aMsg.SetWithCopy(pszContent);

	this->m_vec.push_back(aMsg);

	return nStoredLength;
}

size_t LoggerScope::Push(const Color &rgba, const char *pszContent)
{
	Message aMsg(rgba);

	size_t nStoredLength = aMsg.SetWithCopy(pszContent);

	this->m_vec.push_back(aMsg);

	return nStoredLength;
}

size_t LoggerScope::PushFormat(const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	Message aMsg(this->m_aColor);

	size_t nStoredLength = aMsg.SetWithCopy((const char *)sBuffer);

	this->m_vec.push_back(aMsg);

	return nStoredLength;
}

size_t LoggerScope::PushFormat(const Color &rgba, const char *pszFormat, ...)
{
	char sBuffer[MAX_LOGGING_MESSAGE_LENGTH];

	va_list aParams;

	va_start(aParams, pszFormat);
	V_vsnprintf((char *)sBuffer, sizeof(sBuffer), pszFormat, aParams);
	va_end(aParams);

	Message aMsg(rgba);

	size_t nStoredLength = aMsg.SetWithCopy((const char *)sBuffer);

	this->m_vec.push_back(aMsg);

	return nStoredLength;
}

size_t LoggerScope::Send(SendFunc funcOn)
{
	std::string sResultContent;

	size_t nSize = this->m_vec.size();
	
	for(size_t n = 0; n < nSize; n++)
	{
		sResultContent += this->m_aStartWith + this->m_vec[n].Get() + this->m_aEnd;
	}

	funcOn(sResultContent.c_str());

	return nSize;
}

size_t LoggerScope::SendColor(SendColorFunc funcOn)
{
	std::string sResultContent;

	size_t nSize = this->m_vec.size();

	Color rgbaSave = this->m_aColor;

	for(size_t n = 0; n < nSize; n++)
	{
		const auto &aMsg = this->m_vec[n];

		if(aMsg.GetColor() == rgbaSave)
		{
			sResultContent += this->m_aStartWith + aMsg.Get() + this->m_aEnd;
		}
		else
		{
			funcOn(rgbaSave, sResultContent.c_str());

			sResultContent = this->m_aStartWith + aMsg.Get() + this->m_aEnd;
			rgbaSave = aMsg.GetColor();
		}
	}

	if(sResultContent.size())
	{
		funcOn(rgbaSave, sResultContent.c_str());
	}

	return nSize;
}

LoggerScope::Message::Message(const Color &rgbaInit, const char *pszContent)
 :  m_aColor(rgbaInit),
    m_sContent(pszContent)
{
}

const Color &LoggerScope::Message::GetColor() const
{
	return this->m_aColor;
}

const std::string &LoggerScope::Message::Get() const
{
	return this->m_sContent;
}

size_t LoggerScope::Message::SetWithCopy(const char *pszContent)
{
	this->m_sContent = pszContent;

	return this->m_sContent.size();
}