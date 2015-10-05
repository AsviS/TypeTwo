///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedureQueryStringCompiler.hpp"
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

#define STORED_PROCEDURE Database::StoredProcedure::ParameterTypes<ParamTypes...>::ResultSetTypes<ResultTypes...>
#define STORED_PROCEDURE_TEMPLATES template <typename... ParamTypes> template <typename... ResultTypes>

STORED_PROCEDURE_TEMPLATES
STORED_PROCEDURE::STORED_PROCEDURE_CTOR(std::string name, bool requiresCommit, Connection& database)
: mQueryString(QueryStringCompiler<ParamTypes...>::compile(name))
, mReturnsResultSet(sizeof...(ResultTypes) > 0)
, mRequiresCommit(requiresCommit)
, mDatabase(database)
{

}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
void STORED_PROCEDURE::call(ParamTypes... params) const
{
    try
    {
        otl_stream stream(1, mQueryString.c_str(), mDatabase.getConnection(), mReturnsResultSet);
        stream.set_commit(mRequiresCommit);
        stream.set_all_column_types(otl_all_date2str);

        executeParameters(stream, params...);
    }
    catch(otl_exception& e)
    {
        throwCallExcepton(e.msg);
    }
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template <typename RowType>
std::vector<RowType> STORED_PROCEDURE::call(ParamTypes... params) const
{
    std::vector<RowType> resultSet;
    try
    {
        otl_stream stream(1, mQueryString.c_str(), mDatabase.getConnection(), mReturnsResultSet);
        stream.set_commit(mRequiresCommit);
        stream.set_all_column_types(otl_all_date2str);

        executeParameters(stream, params...);


        if(mReturnsResultSet)
            while(!stream.eof())
            {
                std::tuple<ResultTypes...> rowData;
                auto resultSetTypesIndexSequence = std::make_index_sequence<sizeof...(ResultTypes)>{};
                getRow(rowData, stream, resultSetTypesIndexSequence);
                resultSet.push_back(unpackRowData<RowType>(rowData, resultSetTypesIndexSequence));
            }
    }
    catch(otl_exception& e)
    {
        throwCallExcepton(e.msg);
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

        executeParameters(stream, params...);

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
        throwCallExcepton(e.msg);
    }

    return str;
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
void STORED_PROCEDURE::throwCallExcepton(unsigned char* otlMessage) const
{
    std::cout << "Database error: " << otlMessage << std::endl;
    throw std::logic_error("Procedure '" + mQueryString + "' is invalid. Either its database connection is invalid or its data types are invalid.\n" +
                           "See the database error above for details.");
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
void STORED_PROCEDURE::executeParameters(otl_stream& stream, ParamTypes... params) const
{
    executeInputParameters(stream, params...);
    executeOutputParameters(stream, 0, params...);
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template<typename Tuple, unsigned int... indices>
void STORED_PROCEDURE::getRow(Tuple& tuple, otl_stream& stream, std::index_sequence<indices...>) const
{
    getRowColumn<indices...>(tuple, stream);
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template<typename RowType, unsigned int... indices>
RowType STORED_PROCEDURE::unpackRowData(std::tuple<ResultTypes...>& tuple, std::index_sequence<indices...>) const
{
    return RowType(std::get<indices>(tuple)...);
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template<typename Tuple>
void STORED_PROCEDURE::getRowColumn(Tuple&, otl_stream&) const
{
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template<unsigned int index, unsigned int... indices, typename Tuple>
void STORED_PROCEDURE::getRowColumn(Tuple& tuple, otl_stream& stream) const
{
    stream >> std::get<index>(tuple);
    getRowColumn<indices...>(tuple, stream);
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
void STORED_PROCEDURE::executeInputParameters(otl_stream&) const
{
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template<typename ParamType, typename... RemainingParamTypes>
void STORED_PROCEDURE::executeInputParameters(otl_stream& stream, ParamType currentParam, RemainingParamTypes... remainingParams) const
{
    stream << currentParam;
    executeInputParameters(stream, remainingParams...);
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
void STORED_PROCEDURE::executeOutputParameters(otl_stream&, int currentIndex) const
{
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template<typename ParamType, typename... RemainingParamTypes>
void STORED_PROCEDURE::executeOutputParameters(otl_stream& stream, int currentIndex, ParamType& currentParam, RemainingParamTypes&... remainingParams) const
{
    int tmp;
    if(stream.describe_in_vars(tmp)[currentIndex].param_type > 0)
        stream >> currentParam;

    executeOutputParameters(stream, currentIndex + 1, remainingParams...);
}

///////////////////////////////////


#undef STORED_PROCEDURE
#undef STORED_PROCEDURE_TEMPLATES
