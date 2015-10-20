///////////////////////////////////
// STD C++
#include <stdexcept>
#include <sstream>
///////////////////////////////////

namespace Database { namespace StoredProcedure
{

template<typename... Types>
std::string QueryStringCompiler<Types...>::compile(std::string procedureName)
{
    return "CALL " + procedureName + "(" + QueryStringCompiler<Types...>::typeToString() + ")";
}

///////////////////////////////////

template<typename... Types>
std::string QueryStringCompiler<Types...>::typeToString()
{
    return QueryStringCompiler::typeToString<Types...>();
}

///////////////////////////////////

template<typename... Types>
template<typename T, typename... Types2>
std::string QueryStringCompiler<Types...>::typeToString()
{
    std::stringstream paramStr;
    paramStr << ":f" << sizeof...(Types2) << "<" << toString<T>() << ">";

    if(sizeof...(Types2) > 0)
        paramStr << "," << QueryStringCompiler<Types2...>::typeToString();

    return paramStr.str();
}

///////////////////////////////////

template <typename T>
std::string toString()
{
    throw std::logic_error("Type does not exist.");
}



}}
