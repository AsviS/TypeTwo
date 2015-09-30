///////////////////////////////////
// TypeTwo internal headers
#include "utility.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <sstream>
///////////////////////////////////

///////////////////////////////////
// Crypto++
#include "sha.h"
///////////////////////////////////


char* stringToChar(const std::string& str)
{
	char* cArray = new char[str.size() + 1];
	memcpy(cArray, str.c_str(), str.size());
	cArray[str.size()] = '\0';

	return cArray;
}

///////////////////////////////////

std::string sha512(std::string str)
{

    unsigned char* pbOutputBuffer = new unsigned char[CryptoPP::SHA512::DIGESTSIZE];

    CryptoPP::SHA512().CalculateDigest(pbOutputBuffer, (unsigned char*)str.c_str(), str.size());

    std::stringstream ss;
    str.resize(CryptoPP::SHA512::DIGESTSIZE * 2);
	for (unsigned int i = 0; i < CryptoPP::SHA512::DIGESTSIZE; i++)
	    std::snprintf(&str[i * 2], CryptoPP::SHA512::DIGESTSIZE * 2, "%02x", (unsigned int)pbOutputBuffer[i]);

    delete[] pbOutputBuffer;
    return str;
}
