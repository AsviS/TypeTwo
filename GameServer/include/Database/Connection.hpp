#ifndef TYPETWO_DATABASE_CONNECTION_HPP
#define TYPETWO_DATABASE_CONNECTION_HPP

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

///////////////////////////////////
// OTL4
class otl_connect;
class otl_stream;
///////////////////////////////////

namespace Database
{
/// \brief Database connection
///
class Connection
{
    public:
        /// \brief Constructor
        ///
        /// \param host std::string Host to connect to
        /// \param port int
        /// \param schema std::string Database name / schema.
        /// \param username std::string
        /// \param password std::string
        /// \param std::string driver = "{MySQL ODBC 5.3 ANSI Driver}"
        ///
        ///
        Connection(std::string host, int port, std::string schema, std::string username, std::string password, std::string driver = "{MySQL ODBC 5.3 ANSI Driver}");

        /// \brief Destructor
        ///
        ///
        ///
        ~Connection();

        /// \brief Get otl_connect connection object.
        ///
        /// \return otl_connect&
        ///
        ///
        otl_connect& getConnection();

    private:
        otl_connect& mConnection; ///< otl_connect connection object that is wrapped by this class.
};
}

#endif // TYPETWO_DATABASE_CONNECTION_HPP
