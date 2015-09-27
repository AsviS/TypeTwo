#ifndef TYPETWO_DATABASECONNECTIONS_HPP
#define TYPETWO_DATABASECONNECTIONS_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database.hpp"
///////////////////////////////////


/// \brief Static class containing all database connections.
///
class DatabaseConnections
{
    public:
        static Database DEFAULT; ///< Default connection. At the moment we do not need more than one.
};

#endif // TYPETWO_DATABASECONNECTIONS_HPP

