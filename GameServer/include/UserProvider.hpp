#ifndef TYPETWO_USERPROVIDER_HPP
#define TYPETWO_USERPROVIDER_HPP

///////////////////////////////////
// TypeTwo internal headers
class Database;
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

class UserProvider
{
    public:
        UserProvider(Database& db);
        void getCredentials(std::string username, std::string& hashedPassword, std::string& salt);

    private:
        Database& mDb;
};


#endif // TYPETWO_USERPROVIDER_HPP
