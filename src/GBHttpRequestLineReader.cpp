#include "../include/stdafx.h"

#include "../include/GBHttpRequestLineReader.h"

namespace GenericBoson
{
	bool GBHttpRequestLineReader::Read(std::string_view target)
	{
		return Parse(target);
	}
}