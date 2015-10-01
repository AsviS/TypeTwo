///////////////////////////////////
// TypeTwo internal headers
#include "DatabaseStream.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <iostream>
#include <sstream>
#include <stdexcept>
///////////////////////////////////

///////////////////////////////////
// OTL4
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
///////////////////////////////////

template <typename... Params>
DatabaseStoredProcedure<Params...>::DatabaseStoredProcedure(std::string name,
                                                 std::vector<Param> parameters,
                                                 bool returnsResultSet,
                                                 bool requiresCommit,
                                                 Database& database)
: mQueryString(compileQueryString(name, parameters))
, mParameters(parameters)
, mReturnsResultSet(returnsResultSet)
, mRequiresCommit(requiresCommit)
, mDatabase(database)
{
    if(sizeof...(Params) != mParameters.size())
        throw std::logic_error("Invalid stored procedure. The template parameter count does not match the size of the 'parameters' parameter in the constructor.");
}

///////////////////////////////////

template <typename... Params>
std::unique_ptr<DatabaseStream> DatabaseStoredProcedure<Params...>::call(Params... params, bool toString = false) const
{
    std::unique_ptr<DatabaseStream> dbStream;
    std::cout << mQueryString << std::endl;
    try
    {
        otl_stream& stream = *new otl_stream(1, mQueryString.c_str(), mDatabase.getConnection(), mReturnsResultSet);
        stream.set_commit(mRequiresCommit);
        if(toString)
            stream.set_all_column_types(otl_all_num2str | otl_all_date2str);


        executeInputParameters(stream, 0, params...);
        executeOutputParameters(stream, 0, params...);

        dbStream = std::unique_ptr<DatabaseStream>(new DatabaseStream(&stream));
    }
    catch(otl_exception& e)
    {
        std::cout << "Database error: " << e.msg << std::endl;
    }

    return dbStream;
}

///////////////////////////////////

template <typename... Params>
std::string DatabaseStoredProcedure<Params...>::compileQueryString(std::string name, std::vector<Param> parameters)
{
    std::stringstream params;

    if(parameters.size() > 0)
    {
        unsigned int i = 0;
        for(; i < parameters.size() - 1; i++)
            params << ":f" << i << parameters[i].toString() << ",";

        params << ":f" << i << parameters[i].toString();
    }

    return "CALL " + name + "(" + params.str() + ")";
}

///////////////////////////////////

template <typename... Params>
template <typename CurrentParam, typename... RemainingParams>
void DatabaseStoredProcedure<Params...>::executeInputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam currentParam, RemainingParams... remainingParams) const
{
    if(mParameters[currentIndex].direction == Param::Direction::P_IN ||
       mParameters[currentIndex].direction == Param::Direction::P_INOUT)
    {
        stream << currentParam;
    }
    executeInputParameters(stream, currentIndex + 1, remainingParams...);
}

///////////////////////////////////

template <typename... Params>
template <typename CurrentParam>
void DatabaseStoredProcedure<Params...>::executeInputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam currentParam) const
{
    if(mParameters[currentIndex].direction == Param::Direction::P_IN ||
       mParameters[currentIndex].direction == Param::Direction::P_INOUT)
    {
        stream << currentParam;
    }
}

///////////////////////////////////

template <typename... Params>
template <typename CurrentParam, typename... RemainingParams>
void DatabaseStoredProcedure<Params...>::executeOutputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam& currentParam, RemainingParams&... remainingParams) const
{
    if(mParameters[currentIndex].direction == Param::Direction::P_OUT ||
       mParameters[currentIndex].direction == Param::Direction::P_INOUT)
    {
        stream >> currentParam;
    }

    executeOutputParameters(stream, currentIndex + 1, remainingParams...);
}

///////////////////////////////////

template <typename... Params>
template <typename CurrentParam>
void DatabaseStoredProcedure<Params...>::executeOutputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam& currentParam) const
{
    if(mParameters[currentIndex].direction == Param::Direction::P_OUT ||
       mParameters[currentIndex].direction == Param::Direction::P_INOUT)
    {
        stream >> currentParam;
    }
}
