///////////////////////////////////
// TypeTwo internal headers
#include "utility.hpp"
///////////////////////////////////

template <typename Procedure, typename... Result>
Stream<Procedure, Result...>::Stream(const Procedure& procedure)
: mProcedure(procedure)
, mStream(mProcedure.createStreamPtr())
{
    mStream->set_commit(0);
}

template <typename Procedure, typename... Result>
Stream<Procedure, Result...>::~Stream()
{
    commit();
}

///////////////////////////////////

template <typename Procedure, typename... Result>
template<typename... ParamTypes>
void Stream<Procedure, Result...>::execute(ParamTypes... params)
{
    try
    {
        mProcedure.executeParameters(*mStream, params...);
    }
    catch(otl_exception& e)
    {
        std::cout   << "Failed to perform database query at Database::Stream::FetchDataProtocol::Stream::execute." << std::endl
                    << "Probably an UPDATE/INSERT/DELETE operation with invalid arguments (a primary key set to 0, for example)." << std::endl;
        return;
    }

    getRows(initializeParameterPack<Result>()...);
}

///////////////////////////////////

template <typename Procedure, typename... Result>
std::string Stream<Procedure, Result...>::fetch()
{
    if(mBuffer.size() > 0)
        prependColumnDescription();

    return mBuffer;
}

///////////////////////////////////

template <typename Procedure, typename... Result>
void Stream<Procedure, Result...>::prependColumnDescription()
{
    int numColumns;
    otl_column_desc* columns = mStream->describe_select(numColumns);

    if(numColumns > 0)
    {
        std::stringstream strStream;
        for(int i = 0; i < numColumns - 1; i++)
            strStream << columns[i].dbtype << ' ' << columns[i].name << ',';

        strStream << columns[numColumns - 1].dbtype << ' ' << columns[numColumns - 1].name;

        mBuffer = strStream.str() + mBuffer;
    }
}

template <typename Procedure, typename... Result>
void Stream<Procedure, Result...>::getColumns(std::stringstream&)
{
}

///////////////////////////////////

template <typename Procedure, typename... Result>
template<typename CurrentColumnType, typename... RemainingColumnTypes>
void Stream<Procedure, Result...>::getColumns(std::stringstream& strStream, CurrentColumnType& currentColumn, RemainingColumnTypes&... remainingColumns)
{
    mStream->operator>>(currentColumn);
    strStream << '\n' << currentColumn;
    getColumns(strStream, remainingColumns...);
}

///////////////////////////////////

template <typename Procedure, typename... Result>
template<typename... ColumnTypes>
void Stream<Procedure, Result...>::getRows(ColumnTypes... columns)
{
    std::stringstream strStream;

    while(!mStream->eof())
        getColumns(strStream, columns...);

    mBuffer += strStream.str();
}

///////////////////////////////////

template <typename Procedure, typename... Result>
void Stream<Procedure, Result...>::commit() const
{
    mProcedure.commit();
}

///////////////////////////////////

template<template<typename... a> class Procedure, typename... Result>
Stream<Procedure<Result...>, Result...> create(const Procedure<Result...>& procedure)
{
    return Stream<Procedure<Result...>, Result...>(procedure);
}

///////////////////////////////////

template<template<typename... a> class Procedure, typename... Result, typename... Params>
std::string call(const Procedure<Result...>& procedure, Params... params)
{
    Stream<Procedure<Result...>, Result...> stream(procedure);
    stream.execute(params...);
    return stream.fetch();
}
