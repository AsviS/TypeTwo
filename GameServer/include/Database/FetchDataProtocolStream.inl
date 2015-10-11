///////////////////////////////////
// TypeTwo internal headers
#include "utility.hpp"
///////////////////////////////////

template <typename Procedure, typename... Result>
Stream<Procedure, Result...>::Stream(const Procedure& procedure)
: mProcedure(procedure)
, mStream(mProcedure.createStreamHolder())
{

}

///////////////////////////////////

template <typename Procedure, typename... Result>
template<typename... ParamTypes>
void Stream<Procedure, Result...>::execute(ParamTypes... params)
{
    mProcedure.executeParameters(mStream.stream, params...);
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
    otl_column_desc* columns = mStream.stream.describe_select(numColumns);

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
    mStream.stream >> currentColumn;
    strStream << '\n' << currentColumn;
    getColumns(strStream, remainingColumns...);
}

///////////////////////////////////

template <typename Procedure, typename... Result>
template<typename... ColumnTypes>
void Stream<Procedure, Result...>::getRows(ColumnTypes... columns)
{
    std::stringstream strStream;

    while(!mStream.stream.eof())
        getColumns(strStream, columns...);

    mBuffer += strStream.str();
}

