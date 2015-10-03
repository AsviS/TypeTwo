#ifndef TYPETWO_DATABASE_STORED_PROCEDURES_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURES_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedure.hpp"

#define PARAMS DATABASE_STORED_PROCEDURE_PARAMS
#define RETURNS DATABASE_STORED_PROCEDURE_RETURNS
#define PROCEDURE static DATABASE_STORED_PROCEDURE
///////////////////////////////////


namespace Database
{
class StoredProcedures
{
    public:
        ///////////////////////////////////
        // Declare stored procedures below
        // Don't forget to instantiate them in
        // StoredProcedures.cpp
        ///////////////////////////////////

        PROCEDURE
        (
            GET_UNITS,
            PARAMS(int),
            RETURNS(int, int, int)
         );

        PROCEDURE
        (
            GET_ALL_UNIT_TYPES,
            PARAMS(),
            RETURNS(unsigned int, std::string, int, int, int, int, int)
         );

        PROCEDURE
        (
            GET_ALL_USERS,
            PARAMS(int, int),
            RETURNS(int, std::string, std::string, std::string, std::string)
         );

        PROCEDURE
        (
            GET_USER_CREDENTIALS,
            PARAMS(std::string, std::string&, std::string&),
            RETURNS()
         );

        PROCEDURE
        (
            GET_USER_ID,
            PARAMS(std::string, int&),
            RETURNS()
         );

        ///////////////////////////////////
        // Declare stored procedures above
        ///////////////////////////////////
};
}

///////////////////////////////////
// TypeTwo internal headers
#undef PARAMS
#undef RETURNS
#undef PROCEDURE
///////////////////////////////////

#endif // TYPETWO_DATABASE_STORED_PROCEDURES_HPP
