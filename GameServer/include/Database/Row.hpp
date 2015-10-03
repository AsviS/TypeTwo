#ifndef TYPETWO_DATABASE_ROW_HPP
#define TYPETWO_DATABASE_ROW_HPP

///////////////////////////////////
// STD C++
#include <tuple>
///////////////////////////////////

#define                                         \
DATABASE_ROW_CONSTRUCTOR(NAME, ...)                      \
template <typename... RowDataTypes>             \
NAME(const std::tuple<RowDataTypes...>& data)   \
{                                               \
    std::tie(__VA_ARGS__) = data;               \
}


#define                                                 \
DATABASE_ROW_CUSTOM_CONSTRUCTOR(NAME, PARAM_TYPES, PARAM_NAMES)  \
NAME(const std::tuple<PARAM_TYPES>& data)               \
{                                                       \
    std::tie(PARAM_NAMES) = data;                       \
}

#define DATABASE_ROW_PARAMS(...) __VA_ARGS__
#define DATABASE_ROW_NAMES(...) __VA_ARGS__

namespace Database
{
namespace Row
{
    #define CONSTRUCTOR DATABASE_ROW_CONSTRUCTOR
    #define CUSTOM_CONSTRUCTOR DATABASE_ROW_CUSTOM_CONSTRUCTOR
    #define PARAMS DATABASE_ROW_PARAMS
    #define NAMES DATABASE_ROW_NAMES

    ///////////////////////////////////
    // Declare rows below
    ///////////////////////////////////

    struct Unit
    {
        CONSTRUCTOR(Unit, id, unitTypeId, hp)

        int id;
        int unitTypeId;
        int hp;
    };

    struct UnitType
    {
        CONSTRUCTOR(UnitType, id, name, maxHp, damage, movementSpeed, attackRange, attackSpeed)

        unsigned int id;
        std::string name;
        int maxHp;
        int damage;
        int movementSpeed;
        int attackRange;
        int attackSpeed;
    };

    ///////////////////////////////////
    // Declare rows above
    ///////////////////////////////////

    #undef CONSTRUCTOR
    #undef CUSTOM_CONSTRUCTOR
    #undef PARAMS
    #undef NAMES
}
}

#endif // TYPETWO_DATABASE_ROW_HPP


