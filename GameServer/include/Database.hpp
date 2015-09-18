#ifndef TYPETWO_DATABASE_HPP
#define TYPETWO_DATABASE_HPP

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

///////////////////////////////////
// OTL4
class otl_connect;
class otl_stream;
///////////////////////////////////

/// \brief Database connection
///
class Database
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
        Database(std::string host, int port, std::string schema, std::string username, std::string password, std::string driver = "{MySQL ODBC 5.3 ANSI Driver}");

        /// \brief Destructor
        ///
        ///
        ///
        ~Database();

        /// \brief Get otl_connect connection object.
        ///
        /// \return otl_connect&
        ///
        ///
        otl_connect& getConnection();

    private:
        otl_connect& mConnection; ///< otl_connect connection object that is wrapped by this class.
};

#endif // TYPETWO_DATABASE_HPP