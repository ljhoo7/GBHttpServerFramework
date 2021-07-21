#include "../include/stdafx.h"

#include "../include/GBHttpResponseWriter.h"

namespace GenericBoson
{
	GBHttpResponseWriter::GBHttpResponseWriter(GBExpandedOverlapped* pEol)
		: m_pEol(pEol)
	{
		pEol->m_offset = 0;
	}

	GBHttpResponseWriter::~GBHttpResponseWriter()
	{
		int issueSendResult = IssueSend();
	}

	int GBHttpResponseWriter::IssueSend()
	{
		WSABUF bufToSend;
		bufToSend.buf = m_pEol->m_buffer;
		bufToSend.len = m_pEol->m_offset;
		int sendResult = WSASend(m_pEol->m_socket, &bufToSend, 1, nullptr, 0, m_pEol, nullptr);
		return sendResult;
	}

	// Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
	bool GBHttpResponseWriter::WriteStatusLine(const HttpVersion version, const GBHttpResponse & response, const std::string& reason)
	{
		float versionFloat = ((int)version) / 10.0f;

		int statusCodeInteger = (int)response.GetStatusCode();

		return WriteOneLineToBuffer("HTTP/%.2f %d %s\r\n", versionFloat, statusCodeInteger, Constant::g_cStatusCodeToReasonPhaseMap.at(statusCodeInteger).c_str());
	}

	bool GBHttpResponseWriter::WriteHeader(const std::vector<std::pair<std::string, std::string>>& headerList)
	{
		std::stringstream sstream;

		for(auto riter = headerList.rbegin(); riter != headerList.rend(); ++riter)
		{
			bool ret = WriteOneLineToBuffer("%s: %s\r\n", riter->first.c_str(), riter->second.c_str());
			if (false == ret)
			{
				return false;
			}
		}

		return true;
	}

	bool GBHttpResponseWriter::WriteOneLineToBuffer(const char* format, ...)
	{
		char* pLineStartPosition = &m_pEol->m_buffer[m_pEol->m_offset];

		va_list argList;
		__crt_va_start(argList, format);
		int writtenCountOrErrorCode = _vsprintf_s_l(pLineStartPosition, BUFFER_SIZE - m_pEol->m_offset, format, NULL, argList);
		__crt_va_end(argList);

		if (-1 == writtenCountOrErrorCode)
		{
			return false;
		}

		m_lines.emplace_back(pLineStartPosition, writtenCountOrErrorCode);

		m_pEol->m_offset += writtenCountOrErrorCode;

		return true;
	}
}
