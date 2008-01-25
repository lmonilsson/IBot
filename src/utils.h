#ifndef IRC_UTILS_H
#define IRC_UTILS_H

#include <string>

#include "IRC_types.h"

namespace IRC
{
	namespace utils
	{
		void split_string(IRC::core::packet_t &out, const std::string &input, const std::string &delimiter);
		std::string string_to_lower(std::string s);
	}
}

#endif
