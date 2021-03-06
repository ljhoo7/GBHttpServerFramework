#pragma once

#include "Constant.h"
#include <string_view>

namespace GenericBoson
{
	bool SendResponse(const SOCKET& acceptedSocket, const std::string_view path);

	class GBHttpResponse
	{
		HTTP_STATUS_CODE m_cStatusCode = HTTP_STATUS_CODE::OK;
	public:
		GBHttpResponse() = default;
		GBHttpResponse(const HTTP_STATUS_CODE statusCode);

		GBHttpResponse operator=(GBHttpResponse& rvalue);

		HTTP_STATUS_CODE GetStatusCode() const;
	};
}