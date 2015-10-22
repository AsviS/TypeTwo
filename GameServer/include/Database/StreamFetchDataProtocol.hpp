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

namespace Database { namespace Stream { namespace FetchDataProtocol
{

/// \brief StoredProcedure stream that returns result sets as FetchData subprotocol strings.
///
/// The stream is used for batches of the same
/// query.
///
/// \param typename Procedure StoredProcedure type
/// \param typename... Result StoredProcedure result set types.
///
template <typename Procedure, typename... Result>
class Stream
{
    public:
        /// \brief Constructor
        ///
        /// \param procedure const Procedure& StoredProcedure object to create stream from.
        ///
        ///
        Stream(const Procedure& procedure);

        /// \brief Destructor
        ///
        ///
        ///
        ~Stream();

        /// \brief Reset default constructor to default
        ///
        ///
        ///
        Stream()                            = default;

        /// \brief Reset assignment constructor to default
        ///
        /// \param other Stream&&
        ///
        ///
        Stream(Stream&& other)              = default;

        /// \brief Reset assignment operator to default
        ///
        /// \param other Stream&&
        /// \return Stream&
        ///
        ///
        Stream& operator=(Stream&& other)   = default;

        /// \brief Execute query on stream
        ///
        /// \param typename... ParamTypes Query parameter types
        /// \param params ParamTypes... Query arguments
        /// \return void
        ///
        ///
        template<typename... ParamTypes>
        void execute(ParamTypes... params);

        /// \brief Fetch result set as a string in accordance to the Fetch Data subprotocol.
        ///
        /// \return std::string Fetch Data subprotocol string representing the result set.
        ///
        ///
        std::string fetch();

        /// \brief Commit any modifications of the database to the procedure's connection.
        ///
        /// \return void
        ///
        ///
        void commit() const;

    private:
        /// \brief Prepend descriptions of the stream's result set's columns to mBuffer.
        ///
        /// \return void
        ///
        ///
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

/// \brief Create a stream using only a procedure object.
///
/// This function wraps the Stream constructor, so that
/// the user only has to provide the stored procedure object
/// when creating the stream.
///
/// Example:
/// using namespace Database;
/// auto stream(Stream::FetchDataProtocol::create(StoredProcedures::GET_UNITS));
///
/// \param template<typename... a> class Procedure StoredProcedure type. Automatically deduced.
/// \param typename... Result Given StoredProcedure object's result set types. Automatically deduced.
/// \param procedure const Procedure<Result...>& StoredProcedure object to create stream from.
/// \return Stream<Procedure<Result...>, Result...> Resulting stream object.
///
///
template<template<typename... a> class Procedure, typename... Result>
Stream<Procedure<Result...>, Result...> create(const Procedure<Result...>& procedure);

/// \brief Call a StoredProcedure once.
///
/// Example:
/// using namespace Database;
/// std::string result = Stream::FetchDataProtocol::call(StoredProcedures::GET_UNITS);
///
/// \param template<typename... a> class Procedure StoredProcedure type. Automatically deduced.
/// \param typename... Result Given StoredProcedure object's result set types. Automatically deduced.
/// \param typename... Params Given StoredProcedure object's parameter types. Automatically deduced.
/// \param procedure const Procedure<Result...>& StoredProcedure object to call.
/// \param params Params... Query arguments.
/// \return std::string Fetch Data subprotocol string representing the result set.
///
///
template<template<typename... a> class Procedure, typename... Result, typename... Params>
std::string call(const Procedure<Result...>& procedure, Params... params);

#include "Database/StreamFetchDataProtocol.inl"

}}}



#endif // TYPETWO_DATABASE_STREAM_FETCH_DATA_PROTOCOL_HPP

