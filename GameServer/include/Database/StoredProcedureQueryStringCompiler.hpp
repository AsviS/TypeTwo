#ifndef TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP

///////////////////////////////////
// STD C++
#include <stdexcept>
#include <sstream>
///////////////////////////////////

namespace Database { namespace StoredProcedure
{
    /// \brief Default case of toString functions
    ///
    /// These toString functions return OTL-stream parameter
    /// strings by C++ data types. For example, it may return a
    /// string "int,inout" if called with <int&> as template
    /// parameter.
    ///
    /// \param typename T C++ type to convert to OTL-stream parameter string.
    /// \return std::string OTL-stream corresponding string of C++ data type.
    ///
    ///
    template <typename T>
    std::string toString()
    {
        throw std::logic_error("Type does not exist.");
    }

    /// \brief Convert int to OTL-stream parameter string.
    ///
    /// \return template<> std::string
    ///
    ///
    template<> std::string toString<int>();

    /// \brief Convert int reference to OTL-stream parameter string.
    ///
    /// \return template<> std::string
    ///
    ///
    template<> std::string toString<int&>();

    /// \brief Convert STL string to OTL-stream parameter string.
    ///
    /// \return template<> std::string
    ///
    ///
    template<> std::string toString<std::string>();

    /// \brief Convert STL string reference to OTL-stream parameter string.
    ///
    /// \return template<> std::string
    ///
    ///
    template<> std::string toString<std::string&>();

    /// \brief Compiles a query string for StoredProcedure
    ///
    /// \param typename... Types Data types to use when creating query string
    ///
    template<typename... Types>
    class QueryStringCompiler
    {
        public:
            /// \brief Compile query string
            ///
            /// \param procedureName std::string Name of stored procedure in database.
            /// \return std::string Query string
            ///
            ///
            static std::string compile(std::string procedureName)
            {
                return "CALL " + procedureName + "(" + QueryStringCompiler<Types...>::typeToString() + ")";
            }

            /// \brief Helper function
            ///
            /// \return std::string
            ///
            ///
            static std::string typeToString()
            {
                return QueryStringCompiler::typeToString<Types...>();
            }

        private:
            /// \brief Recursively compile the parameter strings into one parameters string.
            ///
            /// \param typename T Current parameter
            /// \param typename... Types2 Remaining parameters
            /// \return std::string Parameters string
            ///
            ///
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

    /// \brief Compiles a query string with no parameters
    ///
    template<>
    class QueryStringCompiler<>
    {
        public:
            /// \brief Compiler query string
            ///
            /// \param procedureName std::string Name of stored procedure in database.
            /// \return std::string Query string
            ///
            ///
            static std::string compile(std::string procedureName)
            {
                return "CALL " + procedureName + "()";
            }

            /// \brief Helper function
            ///
            /// \return std::string
            ///
            ///
            static std::string typeToString()
            {
                return "";
            }
    };
}}


#endif // TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP



