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
    private:
        typedef StoredProcedureParameter Param;
        typedef Param::Direction Dir;
        typedef Param::Type Type;

    public:
        static const StoredProcedure::ParameterTypes<int>::ResultSetTypes<int, int, int> GET_UNITS;
        static const StoredProcedure::ParameterTypes<int, int>::ResultSetTypes<int, std::string, std::string, std::string, std::string> GET_ALL_USERS;
        static const StoredProcedure::ParameterTypes<std::string, std::string&, std::string&>::ResultSetTypes<> GET_USER_CREDENTIALS;
        static const StoredProcedure::ParameterTypes<std::string, int&>::ResultSetTypes<> GET_USER_ID;
};
}

#endif // TYPETWO_DATABASE_STORED_PROCEDURES_HPP
