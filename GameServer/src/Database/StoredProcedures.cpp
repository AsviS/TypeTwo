///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedures.hpp"
using namespace Database;
///////////////////////////////////


const StoredProcedure
::ParameterTypes<int>
::ResultSetTypes<int, int, int, int>
StoredProcedures::GET_UNITS("unit_getby_userid");

///////////////////////////////////

const StoredProcedure
::ParameterTypes<>
::ResultSetTypes<int, int, int, int, int>
StoredProcedures::GET_ALL_UNITS("unit_get");

///////////////////////////////////

const StoredProcedure
::ParameterTypes<>
::ResultSetTypes<unsigned int, std::string, int, int, int, int, int>
StoredProcedures::GET_ALL_UNIT_TYPES("unit_type_get");

///////////////////////////////////

const StoredProcedure
::ParameterTypes<int, int>
::ResultSetTypes<int, std::string, std::string, std::string, std::string>
StoredProcedures::GET_ALL_USERS("user_get");

///////////////////////////////////

const StoredProcedure
::ParameterTypes<std::string, std::string&, std::string&>
::ResultSetTypes<>
StoredProcedures::GET_USER_CREDENTIALS("user_get_credentials");

///////////////////////////////////

const StoredProcedure
::ParameterTypes<std::string, int&>
::ResultSetTypes<>
StoredProcedures::GET_USER_ID("user_get_id");

///////////////////////////////////

const Database::StoredProcedure
::ParameterTypes<std::string>
::ResultSetTypes<unsigned int, std::string, std::string, std::string, std::string, std::string, std::string>
StoredProcedures::GET_USER_BY_USERNAME("user_getby_username");

///////////////////////////////////

const Database::StoredProcedure
::ParameterTypes<int, int, int, int>
::ResultSetTypes<int, int, int, int, int>
StoredProcedures::INSERT_UNIT("unit_insert", true);

///////////////////////////////////

const Database::StoredProcedure
::ParameterTypes<int>
::ResultSetTypes<int, int, int, int, int>
StoredProcedures::GET_UNITS_BY_ZONE_ID("unit_getby_zoneid");

///////////////////////////////////

const Database::StoredProcedure
::ParameterTypes<int, int>
::ResultSetTypes<int, int, int, int, int>
StoredProcedures::GET_UNITS_BY_USER_ID_AND_ZONE_ID("unit_getby_userid_zoneid");

///////////////////////////////////

const Database::StoredProcedure
::ParameterTypes<>
::ResultSetTypes<int>
StoredProcedures::GET_ALL_ZONES("zone_get");

///////////////////////////////////

const Database::StoredProcedure
::ParameterTypes<int>
::ResultSetTypes<int, int>
StoredProcedures::GET_ZONE_NEIGHBORS("zone_neighbor_getby_zoneid");

///////////////////////////////////

const Database::StoredProcedure
::ParameterTypes<int>
::ResultSetTypes<int, int, int, int, int>
StoredProcedures::GET_UNIT_BY_ID("unit_getby_id");

///////////////////////////////////

const Database::StoredProcedure
::ParameterTypes<int, int>
::ResultSetTypes<>
StoredProcedures::MOVE_UNIT("unit_set_zoneid", true);
