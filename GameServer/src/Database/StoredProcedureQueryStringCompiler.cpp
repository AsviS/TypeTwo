///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedureQueryStringCompiler.hpp"
///////////////////////////////////


namespace Database { namespace StoredProcedure
{
    template<>
    std::string toString<int>()
    {
        return "int,in";
    }
    template<>
    std::string toString<int&>()
    {
        return "int,inout";
    }


    template<>
    std::string toString<std::string>()
    {
        return "char[256],in";
    }

    template<>
    std::string toString<std::string&>()
    {
        return "char[256],inout";
    }
}}
