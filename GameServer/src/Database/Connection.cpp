///////////////////////////////////
// TypeTwo internal headers
#include "Database/Connection.hpp"
using namespace Database;
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


Connection::Connection(std::string host, int port, std::string schema, std::string username, std::string password, std::string driver)
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

Connection::~Connection()
{
    delete &mConnection;
}

///////////////////////////////////

otl_connect& Connection::getConnection()
{
    return mConnection;
}

///////////////////////////////////

void Connection::commit() const
{
    mConnection.commit();
}
