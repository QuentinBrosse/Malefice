#include <boost/algorithm/string.hpp>

#include "StringUtility.h"

std::vector<std::string> utility::StringUtility::explode(const std::string& s, const std::string& delim)
{
	std::vector<std::string> strs;
	boost::split(strs, s, boost::is_any_of("\t "));

	return (strs);
}