#ifndef TYPETWO_DATABASE_ROW_HPP
#define TYPETWO_DATABASE_ROW_HPP

///////////////////////////////////
// STD C++
#include <tuple>
///////////////////////////////////


namespace Database
{
namespace Row
{
    #define                                             \
    ROW_BEGIN(NAME, ...)                                \
    struct NAME                                         \
    {                                                   \
        template <typename... RowDataTypes>             \
        NAME(const std::tuple<RowDataTypes...>& data)   \
        {                                               \
            std::tie(__VA_ARGS__) = data;               \
        }

    #define ROW_END };

///////////////////////////////////
// Declare rows below
///////////////////////////////////

    ROW_BEGIN(Unit, id, unitTypeId, hp)
        int id;
        int unitTypeId;
        int hp;
    ROW_END

    ROW_BEGIN(UnitType, id, name, maxHp, damage, movementSpeed, attackRange, attackSpeed)
        unsigned int id;
        std::string name;
        int maxHp;
        int damage;
        int movementSpeed;
        int attackRange;
        int attackSpeed;
    ROW_END


///////////////////////////////////
// Declare rows above
///////////////////////////////////

    #undef ROW_BEGIN
    #undef ROW_END
}
}

#endif // TYPETWO_DATABASE_ROW_HPP


