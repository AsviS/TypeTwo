#ifndef TYPETWO_DATABASESTOREDPROCEDURES_HPP
#define TYPETWO_DATABASESTOREDPROCEDURES_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "DatabaseStoredProcedure.hpp"
///////////////////////////////////

class DatabaseStoredProcedures
{
    private:
        typedef DatabaseStoredProcedureParameter Param;
        typedef Param::Direction Dir;
        typedef Param::Type Type;

    public:
        static const DatabaseStoredProcedure::ParameterTypes<int>::ResultSetTypes<int, int, int> GET_UNITS;
        static const DatabaseStoredProcedure::ParameterTypes<int, int>::ResultSetTypes<int, std::string, std::string, std::string, std::string> GET_ALL_USERS;
        static const DatabaseStoredProcedure::ParameterTypes<std::string, std::string&, std::string&>::ResultSetTypes<> GET_USER_CREDENTIALS;
        static const DatabaseStoredProcedure::ParameterTypes<std::string, int&>::ResultSetTypes<> GET_USER_ID;
};

#endif // TYPETWO_DATABASESTOREDPROCEDURES_HPP
