///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedureParameter.hpp"
using namespace Database;
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <stdexcept>
///////////////////////////////////


StoredProcedureParameter::StoredProcedureParameter(Type type, Direction direction)
: type(type),
direction(direction)
{

}

///////////////////////////////////

std::string StoredProcedureParameter::toString()
{
    return "<" + typeToString(type) + "," + directionToString(direction) + ">";
}

///////////////////////////////////

std::string StoredProcedureParameter::typeToString(Type type)
{
    switch(type)
    {
        case Type::INT:     return "int";
        case Type::CHAR:    return "char[256]";

        default:
            throw std::logic_error("Parameter type does not exist.");
    }
}

///////////////////////////////////

std::string StoredProcedureParameter::directionToString(Direction direction)
{
    switch(direction)
    {
        case Direction::P_IN:       return "in";
        case Direction::P_OUT:      return "out";
        case Direction::P_INOUT:    return "inout";

        default:
            throw std::logic_error("Parameter direction does not exist.");
    }
}
