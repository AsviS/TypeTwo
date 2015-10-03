#ifndef TYPETWO_DATABASE_CONNECTIONS_HPP
#define TYPETWO_DATABASE_CONNECTIONS_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database/Connection.hpp"
///////////////////////////////////

namespace Database
{
/// \brief Static class containing all database connections.
///
/// These connections must be instantiated elsewhere. Do NOT
/// instantiate them in public code. Only instantiate them in
/// your local files, i.e. your main.cpp.
///
/// Instantiating these in public code will publicize things
/// that should not be made public, i.e. database passwords.
///
class Connections
{
    public:
        static Connection DEFAULT; ///< Default connection. At the moment we do not need more than one.
};
}



#endif // TYPETWO_DATABASE_CONNECTIONS_HPP

