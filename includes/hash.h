#pragma once

#include <cstdlib>
#include <string>

#define assert(x) if(!x)std::exit(EXIT_FAILURE)

typedef unsigned __int64	uint64;

namespace ostl {
	template<typename KEY>
	uint64 hash(const KEY& key) { assert(false); }

	template<>
	uint64 hash<const char*>(const char* const& str) {

		uint64 h = 16777551;
		int len = strlen(str);

		for (int i = 0; i < len; i++) {
			h = (h << 1 | h >> 31) ^ str[i];
		}
		return h;
	}

	template<>
	uint64 hash<char>(const char& key) {
		uint64 val = 3217 * (uint64)key + 4423;
		return ((val ^ ((val << 3) & (val >> 5))) % 1257787);
	}

	template<>
	uint64 hash<int>(const int& key) {
		uint64 val = 3217 * (uint64)key + 4423;
		return ((val ^ ((val << 3) & (val >> 5))) % 1257787);
	}

	template<>
	uint64 hash<float>(const float& key) {
		uint64 val = 3217 * (uint64)key + 4423;
		return ((val ^ ((val << 3) & (val >> 5))) % 1257787);
	}

	template<>
	uint64 hash<double>(const double& key) {
		uint64 val = 3217 * (uint64)key + 4423;
		return ((val ^ ((val << 3) & (val >> 5))) % 1257787);
	}

	template<>
	uint64 hash<uint64>(const uint64& key) {
		uint64 val = 3217 * key + 4423;
		return ((val ^ ((val << 3) & (val >> 5))) % 1257787);
	}

	template<>
	uint64 hash<std::string>(const std::string& str) { return hash(str.c_str()); }
}