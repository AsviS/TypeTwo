///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedures.hpp"
using namespace Database;
///////////////////////////////////

#define PARAMS(...) __VA_ARGS__
#define RETURNS(...) __VA_ARGS__
#define PARAM(TYPE, DIRECTION) StoredProcedureParameter(StoredProcedureParameter::Type::TYPE, StoredProcedureParameter::Direction::P_##DIRECTION)

#define \
STORED_PROCEDURE(NAME, PARAM_TYPES, RETURN_TYPES)\
const StoredProcedure::ParameterTypes<PARAM_TYPES>::ResultSetTypes<RETURN_TYPES> StoredProcedures::NAME\

///////////////////////////////////
// Instantiate stored procedures below
///////////////////////////////////

STORED_PROCEDURE(GET_UNITS,
                 PARAMS(int),
                 RETURNS(int, int, int))
(
    "unit_getby_userid",
    {
        PARAM(INT, IN)
    }
);

///////////////////////////////////

STORED_PROCEDURE(GET_ALL_UNIT_TYPES,
                 PARAMS(),
                 RETURNS(unsigned int, std::string, int, int, int, int, int))
(
    "unit_type_get"
);

///////////////////////////////////

STORED_PROCEDURE(GET_ALL_USERS,
                 PARAMS(int, int),
                 RETURNS(int, std::string, std::string, std::string, std::string))
(
    "user_get",
    {
        PARAM(INT, IN),
        PARAM(INT, IN)
    }
);

///////////////////////////////////

STORED_PROCEDURE(GET_USER_CREDENTIALS,
                 PARAMS(std::string, std::string&, std::string&),
                 RETURNS())
(
    "user_get_credentials",
    {
        PARAM(CHAR, IN),
        PARAM(CHAR, OUT),
        PARAM(CHAR, OUT)
    }
);

///////////////////////////////////

STORED_PROCEDURE(GET_USER_ID,
                 PARAMS(std::string, int&),
                 RETURNS())
(
    "user_get_id",
    {
        PARAM(CHAR, IN),
        PARAM(INT, OUT)
    }
);

///////////////////////////////////
// Instantiate stored procedures above
///////////////////////////////////

#undef PARAMS
#undef PARAM
#undef RETURNS
#undef STORED_PROCEDURE
