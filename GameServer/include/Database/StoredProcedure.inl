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

#define STORED_PROCEDURE Database::StoredProcedure::ParameterTypes<ParamTypes...>::ResultSetTypes<ResultTypes...>
#define STORED_PROCEDURE_TEMPLATES template <typename... ParamTypes> template <typename... ResultTypes>

STORED_PROCEDURE_TEMPLATES
STORED_PROCEDURE::STORED_PROCEDURE_CTOR(std::string name, std::vector<Param> parameters, bool requiresCommit, Connection& database)
: mQueryString(compileQueryString(name, parameters))
, mParameters(parameters)
, mReturnsResultSet(sizeof...(ResultTypes) > 0)
, mRequiresCommit(requiresCommit)
, mDatabase(database)
{
    if(sizeof...(ParamTypes) != mParameters.size())
        throw std::logic_error
        (
            "Invalid stored procedure with name '" + name +
            "'. The template parameter count does not match" +
            " the size of the 'parameters' parameter in the constructor."
        );
}

namespace Database
{
    namespace StoredProcedure
    {
        template <size_t index>
        class getRow
        {
            public:
            template <typename... ResultTypes>
            static void go(std::tuple<ResultTypes...>& tuple, otl_stream& stream)
            {
                stream >> std::get<sizeof...(ResultTypes) - 1 - index>(tuple);
                getRow<index - 1>::go(tuple, stream);
            }
        };

        template <>
        class getRow<0>
        {
            public:
            template <typename... ResultTypes>
            static void go(std::tuple<ResultTypes...>& tuple, otl_stream& stream)
            {
                stream >> std::get<sizeof...(ResultTypes) - 1>(tuple);
            }
        };

        template <>
        class getRow<-1>
        {
            public:
            template <typename... ResultTypes>
            static void go(std::tuple<ResultTypes...>& tuple, otl_stream& stream)
            {
            }
        };
    }
}



STORED_PROCEDURE_TEMPLATES
std::vector<std::tuple<ResultTypes...>> STORED_PROCEDURE::call(ParamTypes... params) const
{
    std::vector<std::tuple<ResultTypes...>> resultSet;
    try
    {
        otl_stream stream(1, mQueryString.c_str(), mDatabase.getConnection(), mReturnsResultSet);
        stream.set_commit(mRequiresCommit);
        stream.set_all_column_types(otl_all_date2str);

        executeInputParameters(stream, 0, params...);
        executeOutputParameters(stream, 0, params...);

        if(mReturnsResultSet)
            while(!stream.eof())
            {
                std::tuple<ResultTypes...> row;
                getRow<sizeof...(ResultTypes) - 1>::go(row, stream);
                resultSet.push_back(row);
            }
    }
    catch(otl_exception& e)
    {
        std::cout << "Database error: " << e.msg << std::endl;
    }

    return resultSet;
}



///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
std::string STORED_PROCEDURE::callAsFetchDataProtocol(ParamTypes... params) const
{
    std::string str;
    try
    {

        otl_stream stream(1, mQueryString.c_str(), mDatabase.getConnection(), mReturnsResultSet);
        stream.set_commit(mRequiresCommit);
        stream.set_all_column_types(otl_all_num2str | otl_all_date2str);

        executeInputParameters(stream, 0, params...);
        executeOutputParameters(stream, 0, params...);

        std::stringstream strStream;
        int numColumns;
        otl_column_desc* columns = stream.describe_select(numColumns);

        if(numColumns > 0)
        {
            for(int i = 0; i < numColumns - 1; i++)
                strStream << columns[i].dbtype << ' ' << columns[i].name << ',';

            strStream << columns[numColumns - 1].dbtype << ' ' << columns[numColumns - 1].name;

            str = strStream.str();
        }

        str.reserve(str.size() +  stream.get_dirty_buf_len());

        if(mReturnsResultSet)
            while(!stream.eof())
            {
                std::string buffer;
                stream >> buffer;
                str.append(1, '\n').append(buffer);
            }
    }
    catch(otl_exception& e)
    {
        std::cout << "Database error: " << e.msg << std::endl;
    }

    return str;
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
std::string STORED_PROCEDURE::compileQueryString(std::string name, std::vector<Param> parameters)
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

STORED_PROCEDURE_TEMPLATES
template <typename CurrentParam, typename... RemainingParams>
void STORED_PROCEDURE::executeInputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam currentParam, RemainingParams... remainingParams) const
{
    if(mParameters[currentIndex].direction == Param::Direction::P_IN ||
       mParameters[currentIndex].direction == Param::Direction::P_INOUT)
    {
        stream << currentParam;
    }
    executeInputParameters(stream, currentIndex + 1, remainingParams...);
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template <typename CurrentParam>
void STORED_PROCEDURE::executeInputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam currentParam) const
{
    if(mParameters[currentIndex].direction == Param::Direction::P_IN ||
       mParameters[currentIndex].direction == Param::Direction::P_INOUT)
    {
        stream << currentParam;
    }
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template <typename CurrentParam, typename... RemainingParams>
void STORED_PROCEDURE::executeOutputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam& currentParam, RemainingParams&... remainingParams) const
{
    if(mParameters[currentIndex].direction == Param::Direction::P_OUT ||
       mParameters[currentIndex].direction == Param::Direction::P_INOUT)
    {
        stream >> currentParam;
    }

    executeOutputParameters(stream, currentIndex + 1, remainingParams...);
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template <typename CurrentParam>
void STORED_PROCEDURE::executeOutputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam& currentParam) const
{
    if(mParameters[currentIndex].direction == Param::Direction::P_OUT ||
       mParameters[currentIndex].direction == Param::Direction::P_INOUT)
    {
        stream >> currentParam;
    }
}


#undef STORED_PROCEDURE
#undef STORED_PROCEDURE_TEMPLATES
