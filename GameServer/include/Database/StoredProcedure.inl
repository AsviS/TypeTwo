///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedureQueryStringCompiler.hpp"
#include "utility.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <iostream>
#include <sstream>
#include <stdexcept>
///////////////////////////////////

#define STORED_PROCEDURE Database::StoredProcedure::ParameterTypes<ParamTypes...>::ResultSetTypes<ResultTypes...>
#define STORED_PROCEDURE_TEMPLATES template <typename... ParamTypes> template <typename... ResultTypes>

STORED_PROCEDURE_TEMPLATES
STORED_PROCEDURE::ResultSetTypes(std::string name, bool requiresCommit, Connection& database)
: M_QUERY_STRING(QueryStringCompiler<ParamTypes...>::compile(name))
, M_RETURNS_RESULT_SET(sizeof...(ResultTypes) > 0)
, M_REQUIRES_COMMIT(requiresCommit)
, mDatabase(database)
{
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
void STORED_PROCEDURE::call(ParamTypes... params) const
{
    otl_stream* stream = createOtlStream();
    execute(*stream, params...);
    delete stream;
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template <typename RowType>
std::vector<RowType> STORED_PROCEDURE::call(ParamTypes... params) const
{
    otl_stream* stream = createOtlStream();
    std::vector<RowType> result = execute<RowType>(*stream, params...);

    delete stream;
    return result;
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
void STORED_PROCEDURE::execute(otl_stream& stream, ParamTypes... params) const
{
    try
    {
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
std::vector<RowType> STORED_PROCEDURE::execute(otl_stream& stream, ParamTypes... params) const
{
    std::vector<RowType> resultSet;
    try
    {
        executeParameters(stream, params...);

        if(M_RETURNS_RESULT_SET)
            resultSet = getRows<RowType>(stream, initializeParameterPack<ResultTypes>()...);
    }
    catch(otl_exception& e)
    {
        throwCallExcepton(e.msg);
    }

    return resultSet;
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
Database::StoredProcedure::StreamPtr STORED_PROCEDURE::createStreamPtr() const
{
    return StreamPtr(createOtlStream());
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
otl_stream* STORED_PROCEDURE::createOtlStream() const
{
    otl_stream* stream;
    try
    {
        stream = new otl_stream(1, M_QUERY_STRING.c_str(), mDatabase.getConnection(), M_RETURNS_RESULT_SET);
        stream->set_commit(M_REQUIRES_COMMIT);
        stream->set_all_column_types(otl_all_date2str);
    }
    catch(otl_exception& e)
    {
        throwCallExcepton(e.msg);
    }

    return stream;
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
void STORED_PROCEDURE::throwCallExcepton(unsigned char* otlMessage) const
{
    std::cout << "Database error: " << otlMessage << std::endl;
    throw std::logic_error("Procedure '" + M_QUERY_STRING + "' is invalid. Either its database connection is invalid or its data types are invalid.\n" +
                           "See the database error above for details.\n\n" +
                           "If the procedure call was fetching a result set, also make sure that\n" +
                           "the Row type used has a constructor that matches the fetched rows' data types.");
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
void STORED_PROCEDURE::getColumns(otl_stream& stream) const
{
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template<typename CurrentColumnType, typename... RemainingColumnTypes>
void STORED_PROCEDURE::getColumns(otl_stream& stream, CurrentColumnType& currentColumn, RemainingColumnTypes&... remainingColumns) const
{
    stream >> currentColumn;
    getColumns(stream, remainingColumns...);
}

///////////////////////////////////

STORED_PROCEDURE_TEMPLATES
template<typename RowType, typename... ColumnTypes>
std::vector<RowType> STORED_PROCEDURE::getRows(otl_stream& stream, ColumnTypes... columns) const
{
    std::vector<RowType> rows;
    while(!stream.eof())
    {
        getColumns(stream, columns...);
        rows.push_back(RowType(columns...));
    }

    return rows;
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
