///////////////////////////////////
// TypeTwo internal headers
#include "CompatibilityWrappers.hpp"
///////////////////////////////////

char* stringToChar(const std::string& str)
{
	char* cArray = new char[str.size() + 1];

	#if (_MSC_VER >= 1400)
	#pragma warning(push)
	#pragma warning(disable: 4996)
	#endif
	str.copy(cArray, str.size());
	#if (_MSC_VER >= 1400)
	#pragma warning(pop)
	#endif
	cArray[str.size()] = '\0';
	return cArray;
}
