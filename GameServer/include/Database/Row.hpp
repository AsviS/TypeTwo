#ifndef TYPETWO_DATABASE_ROW_HPP
#define TYPETWO_DATABASE_ROW_HPP

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

namespace Database
{

/// \brief Commonly used Row types
///
/// A Row type represents a row of data
/// in a result set fetched from a database.
/// These are used in conjunction with the
/// StoredProcedure class.
///
/// For a Row type to be used in a stored
/// procedure call, it must have a constructor
/// with parameters that match the data types
/// of the fetched rows.
///
namespace Row
{
    struct Unit
    {
        Unit(int id, int unitTypeId, int hp)
        : id(id)
        , unitTypeId(unitTypeId)
        , hp(hp)
        {}

        int id;
        int unitTypeId;
        int hp;
    };

    struct UnitType
    {
        UnitType(unsigned int id, std::string name, int maxHp, int damage, int movementSpeed, int attackRange, int attackSpeed)
        : id(id)
        , name(name)
        , maxHp(maxHp)
        , damage(damage)
        , movementSpeed(movementSpeed)
        , attackRange(attackRange)
        , attackSpeed(attackSpeed)
        {}

        unsigned int id;
        std::string name;
        int maxHp;
        int damage;
        int movementSpeed;
        int attackRange;
        int attackSpeed;
    };

    struct User
    {
        User(int id, std::string username, std::string email, std::string timeCreated, std::string lastLoginTime)
        : id(id)
        , username(username)
        , email(email)
        , timeCreated(timeCreated)
        , lastLoginTime(lastLoginTime)
        {}

        User(int id, std::string username, std::string password, std::string salt, std::string email, std::string timeCreated, std::string lastLoginTime)
        : id(id)
        , username(username)
        , password(password)
        , salt(salt)
        , email(email)
        , timeCreated(timeCreated)
        , lastLoginTime(lastLoginTime)
        {}

        unsigned int id;
        std::string username,
                    password,
                    salt,
                    email,
                    timeCreated,
                    lastLoginTime;
    };
}
}

#endif // TYPETWO_DATABASE_ROW_HPP


