///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedures.hpp"
using namespace Database;

#define PARAMS DATABASE_STORED_PROCEDURE_PARAMS
#define RETURNS DATABASE_STORED_PROCEDURE_RETURNS
#define PROCEDURE DATABASE_STORED_PROCEDURE
#define PARAM DATABASE_STORED_PROCEDURE_PARAM
///////////////////////////////////



///////////////////////////////////
// Instantiate stored procedures below
///////////////////////////////////

PROCEDURE(StoredProcedures::GET_UNITS,
                 PARAMS(int),
                 RETURNS(int, int, int))
(
    "unit_getby_userid",
    {
        PARAM(INT, IN)
    }
);

///////////////////////////////////

DATABASE_STORED_PROCEDURE(StoredProcedures::GET_ALL_UNIT_TYPES,
                 PARAMS(),
                 RETURNS(unsigned int, std::string, int, int, int, int, int))
(
    "unit_type_get"
);

///////////////////////////////////

PROCEDURE(StoredProcedures::GET_ALL_USERS,
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

PROCEDURE(StoredProcedures::GET_USER_CREDENTIALS,
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

PROCEDURE(StoredProcedures::GET_USER_ID,
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

///////////////////////////////////
// TypeTwo internal headers
#undef PARAMS
#undef RETURNS
#undef PROCEDURE
#undef PARAM
///////////////////////////////////
