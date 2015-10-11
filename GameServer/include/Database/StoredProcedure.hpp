#ifndef TYPETWO_DATABASE_STORED_PROCEDURE_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURE_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database/Connections.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <vector>
#include <string>
///////////////////////////////////

///////////////////////////////////
// OTL4
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
///////////////////////////////////

namespace Database
{

/// \brief Interface for calling stored procedures in a database.
///
/// The syntax here may be confusing, as the interface is not one
/// class. For examples on how to declare a stored procedure, see
/// StoredProcedures.hpp and StoredProcedures.cpp.
///
namespace StoredProcedure
{
    struct StreamHolder
    {
            otl_stream& stream;

            StreamHolder(otl_stream& stream)
            : stream(stream)
            {

            }

            ~StreamHolder()
            {
                delete &stream;
            }
    };

    /// \brief
    ///
    /// \param typename... ParamTypes Types of the procedure's parameters used when calling the procedure.
    ///
    ///
    template<typename... ParamTypes>
    struct ParameterTypes
    {

        /// \brief
        ///
        /// \param typename... ResultTypes Types of the result set returned by the procedure.
        ///
        ///
        template <typename... ResultTypes>
        class ResultSetTypes
        {
            public:
                /// \brief StoredProcedure constructor
                ///
                /// \param name std::string Name of the stored procedure as seen in the database.
                /// \param false bool requiresCommit= Does the stored procedure require a commit? Is only true if the procedure modifies the database.
                /// \param Connections::DEFAULT Connection& database= Connection to be used when calling the procedure.
                ///
                ///
                ResultSetTypes(std::string name, bool requiresCommit = false, Connection& database = Connections::DEFAULT);

                /// \brief Call the procedure, without fetching any result set.
                ///
                /// \param params ParamTypes... Parameters used to call the procedure.
                /// \return void
                ///
                ///
                void call(ParamTypes... params) const;

                class Stream1
                {
                    private:
                        typedef ParameterTypes<ParamTypes...>::ResultSetTypes<ResultTypes...> Procedure;
                        const Procedure& mProcedure;
                        StreamHolder mStream;

                    public:
                        Stream1(const Procedure& procedure)
                        : mProcedure(procedure)
                        , mStream(mProcedure.createStreamHolder())
                        {

                        }

                        void execute(ParamTypes... params)
                        {
                            mProcedure.execute(mStream, params...);
                        }

                        template<typename RowType>
                        std::vector<RowType> execute(ParamTypes... params)
                        {
                            return mProcedure.execute<RowType>(mStream, params...);
                        }
                };

                StreamHolder createStreamHolder() const;

                Stream1 createStream() const;

                void execute(StreamHolder& stream, ParamTypes... params) const;

                template <typename RowType>
                std::vector<RowType> execute(StreamHolder& stream, ParamTypes... params) const;


                /// \brief Call the procedure and fetch the result set.
                ///
                /// \param typename RowType Row type to store the result set's rows in.
                /// \param params ParamTypes... Parameters used to call the procedure.
                /// \return std::vector<RowType> Result set.
                ///
                ///
                template <typename RowType>
                std::vector<RowType> call(ParamTypes... params) const;

                /// \brief Execute parameters to stream
                ///
                /// First inserts input parameters into the stream. After that it
                /// fetches any output parameters and stores them in the function's
                /// arguments.
                ///
                /// \param stream otl_stream& Stream to execute parameters to.
                /// \param params ParamTypes... Parameters to execute.
                /// \return void
                ///
                ///
                void executeParameters(otl_stream& stream, ParamTypes... params) const;

            private:
                /// \brief Throw a database error message.
                ///
                /// \param otlMessage unsigned char* OTL 4 message to include in message.
                /// \return void
                ///
                ///
                void throwCallExcepton(unsigned char* otlMessage) const;

                /// \brief Catch-function for getColumns
                ///
                /// This function is called instead of getColumns(otl_stream&, CurrentColumnType&, RemainingColumnTypes&...)
                /// when there are no more columns to extract.
                ///
                /// \param stream otl_stream&
                /// \return void
                ///
                ///
                void getColumns(otl_stream& stream) const;

                /// \brief Recursively fetch a row's columns from a stream
                ///
                /// \param typename CurrentColumnType Type of current column.
                /// \param typename... RemainingColumnTypes Types of remaining columns.
                /// \param stream otl_stream& Stream to fetch data from
                /// \param currentColumn CurrentColumnType& Current column output
                /// \param remainingColumns RemainingColumnTypes&... Remaining columns
                /// \return void
                ///
                ///
                template<typename CurrentColumnType, typename... RemainingColumnTypes>
                void getColumns(otl_stream& stream, CurrentColumnType& currentColumn, RemainingColumnTypes&... remainingColumns) const;

                /// \brief Get row data
                ///
                /// \param typename RowType Type of object to store row data in.
                /// \param typename... ColumnTypes Types of columns to extract.
                /// \param stream otl_stream& Stream to fetch data from.
                /// \param columns ColumnTypes... Variables to store output in.
                /// \return RowType Row data formatted as a RowType object.
                ///
                ///
                template<typename RowType, typename... ColumnTypes>
                RowType getRow(otl_stream& stream, ColumnTypes... columns) const;

                /// \brief Catch-function for executeInputParameters
                ///
                /// This function is called instead of executeInputParameters(otl_stream&, ParamType, RemainingParamTypes...)
                /// when there are no input parameters to execute.
                ///
                /// \param otl_stream&
                /// \return void
                ///
                ///
                void executeInputParameters(otl_stream&) const;

                /// \brief Recursively send input parameters into stream
                ///
                /// \param typename ParamType Type of current parameter.
                /// \param typename... RemainingParamTypes Types of remaining parameters.
                /// \param stream otl_stream& Stream to send input to.
                /// \param currentParam ParamType Current input parameter
                /// \param remainingParams RemainingParamTypes... Remaining input parameters
                /// \return void
                ///
                ///
                template<typename ParamType, typename... RemainingParamTypes>
                void executeInputParameters(otl_stream& stream, ParamType currentParam, RemainingParamTypes... remainingParams) const;

                /// \brief Catch-function for executeOutputParameters
                ///
                /// This function is called instead of executeOutputParameters(otl_stream&, int, ParamType&, RemainingParamTypes&...)
                /// when there are no output parameters to execute.
                ///
                /// \param otl_stream&
                /// \param int
                /// \return void
                ///
                ///
                void executeOutputParameters(otl_stream&, int) const;

                /// \brief Recursively fetch output parameters from stream
                ///
                /// \param typename ParamType Type of current parameter
                /// \param typename... RemainingParamTypes Types of remaining parameters
                /// \param stream otl_stream& Stream to fetch data from.
                /// \param currentIndex int Index of current parameter
                /// \param currentParam ParamType& Current parameter
                /// \param remainingParams RemainingParamTypes&... Remaining parameters
                /// \return void
                ///
                ///
                template<typename ParamType, typename... RemainingParamTypes>
                void executeOutputParameters(otl_stream& stream, int currentIndex, ParamType& currentParam, RemainingParamTypes&... remainingParams) const;

            private:
                const std::string M_QUERY_STRING; ///< Query string to execute when the procedure is called
                const bool M_RETURNS_RESULT_SET; ///< Indicates whether this procedure can return a result set or not.
                const bool M_REQUIRES_COMMIT;   ///< Indicates whether this procedure requires a database commit.
                Connection& mDatabase; ///< Connection to a database.
        };
    };
}}

#include "Database/StoredProcedure.inl"


#endif // TYPETWO_DATABASE_STORED_PROCEDURE_HPP

