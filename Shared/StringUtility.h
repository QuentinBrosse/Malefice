#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <ostream>
#include "Export.h"

namespace utility
{
	class MALEFICE_DLL_EXPORT StringUtility
	{
	public:
		StringUtility()		= delete;
		~StringUtility()	= delete;

		static std::vector<std::string> explode(const std::string& s, const std::string& delim);
		static std::string string_format(const std::string fmt, ...);
		template<class T>
		static std::string	pluralize(const std::string& word, const T& nb)
		{
			if (nb > -2 && nb < 2)
				return word;
			return word + "s";
		}
		static std::string	random_string(size_t length)
		{
			auto randchar = []() -> char
			{
				const char charset[] =
					"0123456789"
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					"abcdefghijklmnopqrstuvwxyz";
				const size_t max_index = (sizeof(charset) - 1);
				return charset[rand() % max_index];
			};
			std::string str(length, 0);
			std::generate_n(str.begin(), length, randchar);
			return str;
		}
	};
}
