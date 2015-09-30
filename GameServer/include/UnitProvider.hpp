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
#include <sstream>
///////////////////////////////////

struct DatabaseRow
{
    virtual std::string toString() const = 0;
};

struct UnitType : public DatabaseRow
{
    std::string toString() const
    {
        std::stringstream stream;
        stream  << id << '\n'
                << name << '\n'
                << maxHp << '\n'
                << damage << '\n'
                << movementSpeed << '\n'
                << attackRange << '\n'
                << attackRange << '\n';

        return stream.str();
    };

    unsigned int    id;
    std::string     name;
    int             maxHp;
    int             damage;
    int             movementSpeed;
    int             attackRange;
    int             attackSpeed;
};

struct Unit : public DatabaseRow
{
    std::string toString() const
    {
        std::stringstream stream;
        stream  << id << '\n'
                << unitTypeId << '\n'
                << userId << '\n'
                << hp << '\n';

        return stream.str();
    }

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

        std::string getUnitsAsWebSocketString(unsigned int userId);

    private:
        Database& mDb; ///< Database connection
};


#endif // TYPETWO_UNITPROVIDER_HPP
