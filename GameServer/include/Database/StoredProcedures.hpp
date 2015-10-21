#ifndef TYPETWO_DATABASE_STORED_PROCEDURES_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURES_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedure.hpp"
///////////////////////////////////


namespace Database
{
/// \brief Commonly used stored procedures.
///
struct StoredProcedures
{
    static const StoredProcedure
    ::ParameterTypes<int>
    ::ResultSetTypes<int, int, int, int>
    GET_UNITS; ///< Get units that belong to a user by user's ID.

    ///////////////////////////////////

    static const StoredProcedure
    ::ParameterTypes<>
    ::ResultSetTypes<int, int, int, int, int>
    GET_ALL_UNITS; ///< Get all units

    ///////////////////////////////////

    static const StoredProcedure
    ::ParameterTypes<>
    ::ResultSetTypes<unsigned int, std::string, int, int, int, int, int>
    GET_ALL_UNIT_TYPES; ///< Get all existing unit types.

    ///////////////////////////////////

    static const StoredProcedure
    ::ParameterTypes<int, int>
    ::ResultSetTypes<int, std::string, std::string, std::string, std::string>
    GET_ALL_USERS; ///< Get all users in specified range. For example, to get the first 10 users, call the stored procedure by call(0, 10).

    ///////////////////////////////////

    static const StoredProcedure
    ::ParameterTypes<std::string, std::string&, std::string&>
    ::ResultSetTypes<>
    GET_USER_CREDENTIALS; ///< Get credentials (hashed password and salt) of user by username.

    ///////////////////////////////////

    static const StoredProcedure
    ::ParameterTypes<std::string, int&>
    ::ResultSetTypes<>
    GET_USER_ID; ///< Get user ID by username.

    ///////////////////////////////////

    static const Database::StoredProcedure
    ::ParameterTypes<std::string>
    ::ResultSetTypes<unsigned int, std::string, std::string, std::string, std::string, std::string, std::string>
    GET_USER_BY_USERNAME; ///< Get user by username.

    ///////////////////////////////////

    static const Database::StoredProcedure
    ::ParameterTypes<int, int, int, int>
    ::ResultSetTypes<int, int, int, int, int>
    INSERT_UNIT; ///< Create a unit

    ///////////////////////////////////

    static const Database::StoredProcedure
    ::ParameterTypes<int>
    ::ResultSetTypes<int, int, int, int, int>
    GET_UNITS_BY_ZONE_ID; ///< Get units that are located in specified zone.

    ///////////////////////////////////

    static const Database::StoredProcedure
    ::ParameterTypes<int, int>
    ::ResultSetTypes<int, int, int, int, int>
    GET_UNITS_BY_USER_ID_AND_ZONE_ID; ///< Get units that belong to a specified user and that are located in specified zone.

    ///////////////////////////////////

    static const Database::StoredProcedure
    ::ParameterTypes<int>
    ::ResultSetTypes<int>
    GET_USER_ZONE_IDS; ///< Get all zone IDs where the user has a unit.
};
}

#endif // TYPETWO_DATABASE_STORED_PROCEDURES_HPP
