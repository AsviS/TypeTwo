#ifndef TYPETWO_DATABASE_STORED_PROCEDURES_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURES_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedure.hpp"
///////////////////////////////////


namespace Database
{
class StoredProcedures
{
    public:
        static const StoredProcedure
        ::ParameterTypes<int>
        ::ResultSetTypes<int, int, int>
        GET_UNITS;

        static const StoredProcedure
        ::ParameterTypes<>
        ::ResultSetTypes<unsigned int, std::string, int, int, int, int, int>
        GET_ALL_UNIT_TYPES;

        static const StoredProcedure
        ::ParameterTypes<int, int>
        ::ResultSetTypes<int, std::string, std::string, std::string, std::string>
        GET_ALL_USERS;

        static const StoredProcedure
        ::ParameterTypes<std::string, std::string&, std::string&>
        ::ResultSetTypes<>
        GET_USER_CREDENTIALS;

        static const StoredProcedure
        ::ParameterTypes<std::string, int&>
        ::ResultSetTypes<>
        GET_USER_ID;

        static const Database::StoredProcedure
        ::ParameterTypes<std::string>
        ::ResultSetTypes<unsigned int, std::string, std::string, std::string, std::string, std::string, std::string>
        GET_USER_BY_USERNAME;
};
}

#endif // TYPETWO_DATABASE_STORED_PROCEDURES_HPP
