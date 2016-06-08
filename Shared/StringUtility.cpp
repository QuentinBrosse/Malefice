#include <boost/algorithm/string.hpp>
#include <stdarg.h>

#include "StringUtility.h"

std::vector<std::string> utility::StringUtility::explode(const std::string& s, const std::string& delim)
{
	std::vector<std::string> strs;
	boost::split(strs, s, boost::is_any_of("\t "));

	return (strs);
}

std::string utility::StringUtility::string_format(const std::string fmt, ...) {
	int size = ((int)fmt.size()) * 2 + 50;
	std::string str;
	va_list ap;
	while (1) {
		str.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) {
			str.resize(n);
			return str;
		}
		if (n > -1)
			size = n + 1;
		else
			size *= 2;
	}
	return str;
}