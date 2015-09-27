///////////////////////////////////
// TypeTwo internal headers
#include "UnitProvider.hpp"
#include "Database.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <iostream>
///////////////////////////////////

///////////////////////////////////
// OTL4
#define OTL_ODBC
#include "otlv4.h"
///////////////////////////////////

UnitProvider::UnitProvider(Database& db)
: mDb(db)
{
}

///////////////////////////////////

std::vector<UnitType> UnitProvider::getUnitTypes()
{
    try
    {
        otl_stream output(1, "CALL unit_type_get()", mDb.getConnection(), otl_implicit_select);
        output.set_commit(0);

        std::vector<UnitType> types;
        while(!output.eof())
        {
            UnitType type;
            char* nameBuffer = new char[46];
            output  >> type.id
                    >> nameBuffer
                    >> type.maxHp
                    >> type.damage
                    >> type.movementSpeed
                    >> type.attackRange
                    >> type.attackSpeed;

            type.name.assign(nameBuffer);
            types.push_back(type);
        }

        return types;
    }
    catch(otl_exception& e)
    {
        std::cout << "Database error: " << e.msg << std::endl;
    }
}

///////////////////////////////////

std::vector<Unit> UnitProvider::getUnits(unsigned int userId)
{
    try
    {
        otl_stream output(1, "CALL unit_getby_userid(:f1<int,in>)", mDb.getConnection(), otl_implicit_select);
        output.set_commit(0);

        output << (int)userId;

        std::vector<Unit> units;
        while(!output.eof())
        {
            Unit unit;
            output  >> unit.id
                    >> unit.unitTypeId
                    >> unit.hp;

            unit.userId =  userId;
            units.push_back(unit);
        }

        return units;
    }
    catch(otl_exception& e)
    {
        std::cout << "Database error: " << e.msg << std::endl;
    }
}

