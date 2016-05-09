#pragma once

#include <string>
#include "Export.h"

namespace utility
{
	class MALEFICE_DLL_EXPORT StringUtility
	{
	public:
		StringUtility()		= delete;
		~StringUtility()	= delete;

		template<class T>
		static std::string	pluralize(const std::string& word, const T& nb)
		{
			if (nb > -2 && nb < 2)
				return word;
			return word + "s";
		}
	};
}
