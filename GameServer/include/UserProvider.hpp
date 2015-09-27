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

/// \brief Provide user data from database
///
class UserProvider
{
    public:
        /// \brief Constructor
        ///
        /// \param db Database& Database connection
        ///
        ///
        UserProvider(Database& db);

        /// \brief Get user credentials
        ///
        /// \param username std::string Username to search for.
        /// \param hashedPassword std::string& Outputs hashed password stored in database
        /// \param salt std::string& Outputs salt stored in database.
        /// \return void
        ///
        ///
        void getCredentials(std::string username, std::string& hashedPassword, std::string& salt);


        unsigned int getId(std::string username);

    private:
        Database& mDb; ///< Database connection
};


#endif // TYPETWO_USERPROVIDER_HPP
