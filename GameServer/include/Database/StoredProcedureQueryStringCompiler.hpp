#ifndef TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

namespace Database { namespace StoredProcedure
{
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
            static std::string compile(std::string procedureName);

            /// \brief Helper function
            ///
            /// \return std::string
            ///
            ///
            static std::string typeToString();

        private:
            /// \brief Recursively compile the parameter strings into one parameters string.
            ///
            /// \param typename T Current parameter
            /// \param typename... Types2 Remaining parameters
            /// \return std::string Parameters string
            ///
            ///
            template<typename T, typename... Types2>
            static std::string typeToString();
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
            static std::string compile(std::string procedureName);

            /// \brief Helper function
            ///
            /// \return std::string
            ///
            ///
            static std::string typeToString();
    };

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
    std::string toString();

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
}}

#include "Database/StoredProcedureQueryStringCompiler.inl"

#endif // TYPETWO_DATABASE_STORED_PROCEDURE_QUERY_STRING_COMPILER_HPP



