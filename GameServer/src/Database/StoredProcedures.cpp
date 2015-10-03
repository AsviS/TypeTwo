///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedures.hpp"
using namespace Database;
///////////////////////////////////


const StoredProcedure::ParameterTypes<int>::ResultSetTypes<int, int, int> StoredProcedures::GET_UNITS
(
    "unit_getby_userid",
    {
        Param(Type::INT, Dir::P_IN)
    }
);

const StoredProcedure
::ParameterTypes<int, int>
::ResultSetTypes<int, std::string, std::string, std::string, std::string>
StoredProcedures::GET_ALL_USERS
(
    "user_get",
    {
        Param(Type::INT, Dir::P_IN),
        Param(Type::INT, Dir::P_IN)
    }
);

const StoredProcedure::ParameterTypes<std::string, std::string&, std::string&>::ResultSetTypes<> StoredProcedures::GET_USER_CREDENTIALS
(
    "user_get_credentials",
    {
        Param(Type::CHAR, Dir::P_IN),
        Param(Type::CHAR, Dir::P_OUT),
        Param(Type::CHAR, Dir::P_OUT)
    }
);

const StoredProcedure::ParameterTypes<std::string, int&>::ResultSetTypes<> StoredProcedures::GET_USER_ID
{
    "user_get_id",
    {
        Param(Type::CHAR, Dir::P_IN),
        Param(Type::INT, Dir::P_OUT)
    }
};
