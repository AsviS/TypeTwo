///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedureQueryStringCompiler.hpp"
///////////////////////////////////


namespace Database { namespace StoredProcedure
{
    std::string QueryStringCompiler<>::compile(std::string procedureName)
    {
        return "CALL " + procedureName + "()";
    }

    ///////////////////////////////////

    std::string QueryStringCompiler<>::typeToString()
    {
        return "";
    }

    ///////////////////////////////////

    template<>
    std::string toString<int>()
    {
        return "int,in";
    }

    ///////////////////////////////////

    template<>
    std::string toString<int&>()
    {
        return "int,inout";
    }

    ///////////////////////////////////

    template<>
    std::string toString<std::string>()
    {
        return "char[256],in";
    }

    ///////////////////////////////////

    template<>
    std::string toString<std::string&>()
    {
        return "char[256],inout";
    }
}}
