///////////////////////////////////
// TypeTwo internal headers
#include "Database.hpp"
///////////////////////////////////

///////////////////////////////////
// OTL4
#define OTL_ODBC
#include "otlv4.h"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <sstream>
///////////////////////////////////


Database::Database(std::string host, int port, std::string schema, std::string username, std::string password, std::string driver)
: mConnection(*(new otl_connect()))
{
    otl_connect::otl_initialize();

    std::stringstream connectionStr;
    connectionStr   << "SERVER="    << host << ";"
                    << "PORT="      << port << ";"
                    << "DATABASE="  << schema << ";"
                    << "USER="      << username << ";"
                    << "PASSWORD="  << password << ";"
                    << "DRIVER="    << driver << ";";

    mConnection.rlogon(connectionStr.str().c_str());
}

///////////////////////////////////

Database::~Database()
{
    delete &mConnection;
}

///////////////////////////////////

otl_connect& Database::getConnection()
{
    mConnection.commit();
    return mConnection;
}
