///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedures.hpp"
using namespace Database;
///////////////////////////////////


const StoredProcedure
::ParameterTypes<int>
::ResultSetTypes<int, int, int>
StoredProcedures::GET_UNITS("unit_getby_userid");

const StoredProcedure
::ParameterTypes<>
::ResultSetTypes<unsigned int, std::string, int, int, int, int, int>
StoredProcedures::GET_ALL_UNIT_TYPES("unit_type_get");

const StoredProcedure
::ParameterTypes<int, int>
::ResultSetTypes<int, std::string, std::string, std::string, std::string>
StoredProcedures::GET_ALL_USERS("user_get");

const StoredProcedure
::ParameterTypes<std::string, std::string&, std::string&>
::ResultSetTypes<>
StoredProcedures::GET_USER_CREDENTIALS("user_get_credentials");

const StoredProcedure
::ParameterTypes<std::string, int&>
::ResultSetTypes<>
StoredProcedures::GET_USER_ID("user_get_id");

const Database::StoredProcedure
::ParameterTypes<std::string>
::ResultSetTypes<unsigned int, std::string, std::string, std::string, std::string, std::string, std::string>
StoredProcedures::GET_USER_BY_USERNAME("user_getby_username");
