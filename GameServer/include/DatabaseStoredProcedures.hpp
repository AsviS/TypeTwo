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
        static const DatabaseStoredProcedure<int> GET_UNITS;
        static const DatabaseStoredProcedure<std::string, std::string&, std::string&> GET_USER_CREDENTIALS;
        static const DatabaseStoredProcedure<std::string, int&> GET_USER_ID;
};

#endif // TYPETWO_DATABASESTOREDPROCEDURES_HPP
