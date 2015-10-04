#ifndef TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP

///////////////////////////////////
// STD C++
#include <stdexcept>
#include <sstream>
///////////////////////////////////

namespace Database { namespace StoredProcedure
{
    template <typename T>
    std::string toString()
    {
        throw std::logic_error("Type does not exist.");
    }

    template<> std::string toString<int>();
    template<> std::string toString<int&>();
    template<> std::string toString<std::string>();
    template<> std::string toString<std::string&>();

    template<typename... Types>
    class QueryStringCompiler
    {
        public:
            static std::string compile(std::string procedureName)
            {
                return "CALL " + procedureName + "(" + QueryStringCompiler<Types...>::typeToString() + ")";
            }

            static std::string typeToString()
            {
                return QueryStringCompiler::typeToString<Types...>();
            }

        private:
            template<typename T, typename... Types2>
            static std::string typeToString()
            {
                std::stringstream paramStr;
                paramStr << ":f" << sizeof...(Types2) << "<" << toString<T>() << ">";

                if(sizeof...(Types2) > 0)
                    paramStr << "," << QueryStringCompiler<Types2...>::typeToString();

                return paramStr.str();
            }
    };

    template<>
    class QueryStringCompiler<>
    {
        public:
            static std::string compile(std::string procedureName)
            {
                return "CALL " + procedureName + "()";
            }

            static std::string typeToString()
            {
                return "";
            }
    };
}}


#endif // TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP



