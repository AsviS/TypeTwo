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

#define STORED_PROCEDURE_CTOR ResultSetTypes

namespace Database { namespace StoredProcedure
{
    template<typename... ParamTypes>
    struct ParameterTypes
    {
        template <typename... ResultTypes>
        class ResultSetTypes
        {
            private:
                enum class ParamDirection
                {
                    P_IN = 0,
                    P_INOUT = 2,
                };
            public:
                STORED_PROCEDURE_CTOR(std::string name, bool requiresCommit = false, Connection& database = Connections::DEFAULT);

                void call(ParamTypes... params) const;

                template <typename RowType>
                std::vector<RowType> call(ParamTypes... params) const;

                std::string callAsFetchDataProtocol(ParamTypes... params) const;

            private:
                void throwCallExcepton(unsigned char* otlMessage) const;
                void executeParameters(otl_stream& stream, ParamTypes... params) const;

                template<typename Type>
                Type initializeParameterPack() const;

                void getColumns(otl_stream& stream) const;

                template<typename CurrentColumnType, typename... RemainingColumnTypes>
                void getColumns(otl_stream& stream, CurrentColumnType& currentColumn, RemainingColumnTypes&... remainingColumns) const;

                template<typename RowType, typename... ColumnTypes>
                RowType getRow(otl_stream& stream, ColumnTypes... columns) const;


                void executeInputParameters(otl_stream&) const;

                template<typename ParamType, typename... RemainingParamTypes>
                void executeInputParameters(otl_stream& stream, ParamType currentParam, RemainingParamTypes... remainingParams) const;


                void executeOutputParameters(otl_stream&, int) const;

                template<typename ParamType, typename... RemainingParamTypes>
                void executeOutputParameters(otl_stream& stream, int currentIndex, ParamType& currentParam, RemainingParamTypes&... remainingParams) const;

            private:
                std::string mQueryString;
                bool mReturnsResultSet;
                bool mRequiresCommit;
                Connection& mDatabase;
        };
    };
}}

#include "Database/StoredProcedure.inl"

#undef STORED_PROCEDURE_CTOR


#endif // TYPETWO_DATABASE_STORED_PROCEDURE_HPP

