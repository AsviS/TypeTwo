#ifndef TYPETWO_UTILITY_HPP
#define TYPETWO_UTILITY_HPP

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

/// \brief Convert string to char array
///
/// \param str const std::string&
/// \return char*
///
///
char* stringToChar(const std::string& str);


/// \brief Hash string with sha512 algorithm
///
/// \param str std::string String to hash
/// \return std::string Hashed string
///
///
std::string sha512(std::string str);


#endif // TYPETWO_UTILITY_HPP
