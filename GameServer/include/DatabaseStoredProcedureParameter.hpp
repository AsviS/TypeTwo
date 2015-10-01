#ifndef TYPETWO_DATABASESTOREDPROCEDUREPARAMETER_HPP
#define TYPETWO_DATABASESTOREDPROCEDUREPARAMETER_HPP


///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////


struct DatabaseStoredProcedureParameter
{
    enum class Type
    {
        INT,
        CHAR,
        STRING = CHAR,
        VARCHAR = CHAR,
        TINYTEXT = CHAR,
    };

    enum class Direction
    {
        P_IN,
        P_OUT,
        P_INOUT,
    };


    DatabaseStoredProcedureParameter(Type type, Direction direction);
    std::string toString();
    std::string typeToString(Type type);
    std::string directionToString(Direction direction);

    Type type;
    Direction direction;
};

#endif // TYPETWO_DATABASESTOREDPROCEDUREPARAMETER_HPP

