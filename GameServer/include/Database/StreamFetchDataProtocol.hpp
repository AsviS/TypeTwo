#ifndef TYPETWO_DATABASE_STREAM_FETCH_DATA_PROTOCOL_HPP
#define TYPETWO_DATABASE_STREAM_FETCH_DATA_PROTOCOL_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedure.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

namespace Database
{
namespace Stream
{
namespace FetchDataProtocol
{
template <typename Procedure, typename... Result>
class Stream
{
    public:
        Stream(const Procedure& procedure);

        template<typename... ParamTypes>
        void execute(ParamTypes... params);

        /// \brief Fetch result set as a string in accordance to the Fetch Data subprotocol.
        ///
        /// \return std::string Fetch Data subprotocol string representing the result set.
        ///
        ///
        std::string fetch();

    private:
        void prependColumnDescription();

        /// \brief Catch-function for getColumns
        ///
        /// This function is called instead of
        /// getColumn(std::stringstream&, CurrentColumnType&, RemainingColumnTypes&...)
        /// when there are no more columns to extract.
        ///
        /// \param std::stringstream&
        /// \return void
        ///
        ///
        void getColumns(std::stringstream&);

        /// \brief Recursively fetch a row's columns
        ///
        /// \param typename CurrentColumnType Type of current column.
        /// \param typename... RemainingColumnTypes Types of remaining columns.
        /// \param std::stringstream& Stringstream to store row in.
        /// \param currentColumn CurrentColumnType& Current column output
        /// \param remainingColumns RemainingColumnTypes&... Remaining columns
        /// \return void
        ///
        ///
        template<typename CurrentColumnType, typename... RemainingColumnTypes>
        void getColumns(std::stringstream& strStream, CurrentColumnType& currentColumn, RemainingColumnTypes&... remainingColumns);

        /// \brief Get row data
        ///
        /// \param typename RowType Type of object to store row data in.
        /// \param typename... ColumnTypes Types of columns to extract.
        /// \param columns ColumnTypes... Variables to store output in.
        /// \return void
        ///
        ///
        template<typename... ColumnTypes>
        void getRows(ColumnTypes... columns);

    private:
        const Procedure& mProcedure; ///< Procedure to call
        StoredProcedure::StreamPtr mStream; ///< Stream connected to database to call through
        std::string mBuffer; ///< Fetched data.
};

template<template<typename... a> class Procedure, typename... Result>
Stream<Procedure<Result...>, Result...> create(const Procedure<Result...>& procedure);

template<template<typename... a> class Procedure, typename... Result, typename... Params>
std::string call(const Procedure<Result...>& procedure, Params... params);

#include "Database/StreamFetchDataProtocol.inl"

}}}



#endif // TYPETWO_DATABASE_STREAM_FETCH_DATA_PROTOCOL_HPP

