#ifndef TYPETWO_UNITPROVIDER_HPP
#define TYPETWO_UNITPROVIDER_HPP

///////////////////////////////////
// TypeTwo internal headers
class Database;
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <string>
#include <vector>
///////////////////////////////////

struct UnitType
{
    unsigned int    id;
    std::string     name;
    int             maxHp;
    int             damage;
    int             movementSpeed;
    int             attackRange;
    int             attackSpeed;
};

struct Unit
{
    unsigned int id;
    unsigned int unitTypeId;
    unsigned int userId;

    int hp;
};

/// \brief Provide user data from database
///
class UnitProvider
{
    public:
        /// \brief Constructor
        ///
        /// \param db Database& Database connection
        ///
        ///
        UnitProvider(Database& db);

        std::vector<UnitType> getUnitTypes();

        std::vector<Unit> getUnits(unsigned int userId);

    private:
        Database& mDb; ///< Database connection
};


#endif // TYPETWO_UNITPROVIDER_HPP
