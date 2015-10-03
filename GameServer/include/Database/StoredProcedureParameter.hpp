#ifndef TYPETWO_DATABASE_STORED_PROCEDURE_PARAMETER_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURE_PARAMETER_HPP


///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

namespace Database
{
struct StoredProcedureParameter
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


    StoredProcedureParameter(Type type, Direction direction);
    std::string toString();
    std::string typeToString(Type type);
    std::string directionToString(Direction direction);

    Type type;
    Direction direction;
};
}


#endif // TYPETWO_DATABASE_STORED_PROCEDURE_PARAMETER_HPP

