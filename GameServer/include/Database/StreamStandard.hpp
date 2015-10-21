#ifndef TYPETWO_DATABASE_STREAM_STANDARD_HPP
#define TYPETWO_DATABASE_STREAM_STANDARD_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database/StoredProcedure.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <vector>
#include <memory>
///////////////////////////////////

namespace Database{ namespace Stream { namespace Standard
{
/// \brief Standard StoredProcedure stream
///
/// The stream is used for batches of the same
/// query.
///
template<typename Procedure>
class Stream
{
    public:
        /// \brief Constructor
        ///
        /// \param procedure const Procedure& StoredProcedure object to create stream from.
        ///
        ///
        Stream(const Procedure& procedure);

        /// \brief Execute query on stream
        ///
        /// \param typename... ParamTypes Query parameter types
        /// \param params ParamTypes... Query arguments
        /// \return void
        ///
        ///
        template<typename... ParamTypes>
        void execute(ParamTypes... params);

        /// \brief Execute a query on the stream and fetch result set.
        ///
        /// \param typename RowType Row type to store the result set's rows in.
        /// \param typename... ParamTypes Query parameter types.
        /// \param params ParamTypes... Query arguments
        /// \return std::vector<RowType> Result set formatted as RowType data.
        ///
        ///
        template<typename RowType, typename... ParamTypes>
        void execute(std::vector<RowType>& rows, ParamTypes... params);


        void commit() const;

    private:
        const Procedure& mProcedure; ///< StoredProcedure object to execute queries with
        StoredProcedure::StreamPtr mStream; ///< Stream pointer to execute queries on
};

/// \brief Create a stream using only a procedure object.
///
/// This function wraps the Stream constructor, so that
/// the user only has to provide the stored procedure object
/// when creating the stream.
///
/// Example:
/// using namespace Database;
/// auto stream(Stream::Standard::create(StoredProcedures::GET_UNITS));
///
/// \param typename Procedure StoredProcedure type. Automatically deduced.
/// \param procedure const Procedure& StoredProcedure object to create stream from.
/// \return Stream<Procedure> Resulting stream object.
///
///
template<typename Procedure>
Stream<Procedure> create(const Procedure& procedure);

#include "Database/StreamStandard.inl"
}}}


#endif // TYPETWO_DATABASE_STREAM_STANDARD_HPP

