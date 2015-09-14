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
	    //ss << std::hex << (unsigned int)pbOutputBuffer[i];
	    std::snprintf(&str[i * 2], CryptoPP::SHA512::DIGESTSIZE * 2, "%02x", (unsigned int)pbOutputBuffer[i]);

    delete[] pbOutputBuffer;
    return str;
    //return str;
    /*
    std::cout << ss.str() << std::endl;
    return ss.str();


    unsigned char* md_value = new unsigned char[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, EVP_sha512(), NULL);
    EVP_DigestUpdate(mdctx, str.c_str(), str.size());
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_destroy(mdctx);

    str.resize(md_len * 2);
	for (unsigned int i = 0; i < md_len; i++)
	{
		#if (_MSC_VER >= 1400)
		#pragma warning(push)
		#pragma warning(disable: 4996)
		#endif
				sprintf(&str[i * 2], "%02x", (unsigned int)md_value[i]);
		#if (_MSC_VER >= 1400)
		#pragma warning(pop)
		#endif
	}



    delete[] md_value;*/
    return str;
}
