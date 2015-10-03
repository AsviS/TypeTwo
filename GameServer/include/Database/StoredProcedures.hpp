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
        #define PARAMS(...) __VA_ARGS__
        #define RETURNS(...) __VA_ARGS__

        #define \
        STORED_PROCEDURE(NAME, PARAM_TYPES, RETURN_TYPES)\
        static const StoredProcedure::ParameterTypes<PARAM_TYPES>::ResultSetTypes<RETURN_TYPES> NAME\

        ///////////////////////////////////
        // Declare stored procedures below
        // Don't forget to instantiate them in
        // StoredProcedures.cpp
        ///////////////////////////////////

        STORED_PROCEDURE(GET_UNITS,
                         PARAMS(int),
                         RETURNS(int, int, int));

        STORED_PROCEDURE(GET_ALL_UNIT_TYPES,
                         PARAMS(),
                         RETURNS(unsigned int, std::string, int, int, int, int, int));

        STORED_PROCEDURE(GET_ALL_USERS,
                         PARAMS(int, int),
                         RETURNS(int, std::string, std::string, std::string, std::string));

        STORED_PROCEDURE(GET_USER_CREDENTIALS,
                         PARAMS(std::string, std::string&, std::string&),
                         RETURNS());

        STORED_PROCEDURE(GET_USER_ID,
                         PARAMS(std::string, int&),
                         RETURNS());

        ///////////////////////////////////
        // Declare stored procedures above
        ///////////////////////////////////

        #undef PARAMS
        #undef RETURNS
        #undef STORED_PROCEDURE
};
}

#endif // TYPETWO_DATABASE_STORED_PROCEDURES_HPP
