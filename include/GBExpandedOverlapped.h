#pragma once

#include <queue>

namespace GenericBoson
{
	const int BUFFER_SIZE = 4096;

	enum class IO_TYPE : uint64_t
	{
		ACCEPT = 1,
		RECEIVE,
		SEND,
	};

	enum class PARSE_LINE_STATE : uint8_t
	{
		CR_READ,
		LF_READ,
		CRLF_READ,
		OTHER_READ,
	};

	struct GBExpandedOverlapped : public WSAOVERLAPPED
	{
		SOCKET m_socket = INVALID_SOCKET;
		IO_TYPE m_type = IO_TYPE::ACCEPT;

		// #ToDo
		// This must be exchanged with a circular lock-free queue.
		char m_recvBuffer[BUFFER_SIZE] = { 0, };
		char m_sendBuffer[BUFFER_SIZE] = { 0, };

		int m_test = 0;

		DWORD m_recvOffset = 0, m_sendOffset = 0;

		/*
		lines parsed by GatherAndParseLines function.
		*/
		std::queue<std::string_view> m_lines;
		
		/*
		GatherAndParseLines the HTTP message with gathering.

		\return Was It succeeded?
		*/
		bool GatherAndParseLines(DWORD receivedBytes);
	};
}