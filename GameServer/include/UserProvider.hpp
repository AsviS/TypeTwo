#ifndef TYPETWO_USER_PROVIDER_HPP
#define TYPETWO_USER_PROVIDER_HPP

///////////////////////////////////
// TypeTwo internal headers
namespace Database
{
    class Connection;
}
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
        /// \param db DatabaseConnection& Database connection
        ///
        ///
        UserProvider(Database::Connection& db);

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
        Database::Connection& mDb; ///< Database connection
};


#endif // TYPETWO_USER_PROVIDER_HPP
