///////////////////////////////////
// TypeTwo internal headers
#include "UserProvider.hpp"
#include "Database.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <iostream>
///////////////////////////////////

///////////////////////////////////
// OTL4
#define OTL_ODBC
#include "otlv4.h"
///////////////////////////////////

UserProvider::UserProvider(Database& db)
: mDb(db)
{
}

///////////////////////////////////

void UserProvider::getCredentials(std::string username, std::string& hashedPassword, std::string& salt)
{
    try
    {
        otl_stream output(1, "CALL user_get_credentials(:f1<char[17],in>, :f2<char[129],out>, :f3<char[256],out>)", mDb.getConnection());
        output.set_commit(0);
        output << username.c_str();
        char* hashedPasswordBuffer = new char[129];
        char* saltBuffer = new char[256];

        output >> hashedPasswordBuffer >> saltBuffer;


        hashedPassword.assign(hashedPasswordBuffer);
        salt.assign(saltBuffer);
    }
    catch(otl_exception& e)
    {
        std::cout << "Database error: " << e.msg << std::endl;
    }
}

///////////////////////////////////

unsigned int UserProvider::getId(std::string username)
{
    try
    {
        otl_stream output(1, "CALL user_get_id(:f1<char[17],in>, :f2<int,out>)", mDb.getConnection());
        output.set_commit(0);
        output << username.c_str();

        int userId;
        output >> userId;

        return userId;
    }
    catch(otl_exception& e)
    {
        std::cout << "Database error: " << e.msg << std::endl;
    }
}
