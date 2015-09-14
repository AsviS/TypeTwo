///////////////////////////////////
// TypeTwo internal headers
#include "utility.hpp"
///////////////////////////////////

///////////////////////////////////
// OpenSSL
#include "openssl/evp.h"
///////////////////////////////////

std::string sha512(std::string str)
{
    unsigned char* md_value = new unsigned char[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, EVP_sha512(), NULL);
    EVP_DigestUpdate(mdctx, str.c_str(), str.size());
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_destroy(mdctx);

    str.resize(md_len * 2);
    for(unsigned int i = 0; i < md_len; i++)
        sprintf(&str[i*2], "%02x", (unsigned int)md_value[i]);

    delete[] md_value;
    return str;
}
