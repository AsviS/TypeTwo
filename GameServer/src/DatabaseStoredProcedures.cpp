///////////////////////////////////
// TypeTwo internal headers
#include "DatabaseStoredProcedures.hpp"
///////////////////////////////////


const DatabaseStoredProcedure<int> DatabaseStoredProcedures::GET_UNITS
(
    "unit_getby_userid",
    {
        Param(Type::INT, Dir::P_IN)
    },
    true
);

const DatabaseStoredProcedure<std::string, std::string&, std::string&> DatabaseStoredProcedures::GET_USER_CREDENTIALS
(
    "user_get_credentials",
    {
        Param(Type::CHAR, Dir::P_IN),
        Param(Type::CHAR, Dir::P_OUT),
        Param(Type::CHAR, Dir::P_OUT)
    }
);

const DatabaseStoredProcedure<std::string, int&> DatabaseStoredProcedures::GET_USER_ID
{
    "user_get_id",
    {
        Param(Type::CHAR, Dir::P_IN),
        Param(Type::INT, Dir::P_OUT)
    }
};
