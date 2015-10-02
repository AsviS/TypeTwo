#ifndef TYPETWO_DATABASESTOREDPROCEDURE_HPP
#define TYPETWO_DATABASESTOREDPROCEDURE_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "DatabaseConnections.hpp"
#include "DatabaseStoredProcedureParameter.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <vector>
#include <memory>
///////////////////////////////////

#define STORED_PROCEDURE_CTOR ResultSetTypes

namespace DatabaseStoredProcedure
{
template<typename... ParamTypes>
struct ParameterTypes
{
template <typename... ResultTypes>
class ResultSetTypes
{
    private:

    public:
        typedef DatabaseStoredProcedureParameter Param;


        STORED_PROCEDURE_CTOR(std::string name, std::vector<Param> parameters, bool requiresCommit = false, Database& database = DatabaseConnections::DEFAULT);


        std::vector<std::tuple<ResultTypes...>> call(ParamTypes... params) const;
        std::string callAsFetchDataProtocol(ParamTypes... params) const;

    private:
        std::string compileQueryString(std::string name, std::vector<Param> parameters);

        template <typename CurrentParam, typename... RemainingParams>
        void executeInputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam currentParam, RemainingParams... remainingParams) const;

        template <typename CurrentParam>
        void executeInputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam currentParam) const;

        template <typename CurrentParam, typename... RemainingParams>
        void executeOutputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam& currentParam, RemainingParams&... remainingParams) const;

        template <typename CurrentParam>
        void executeOutputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam& currentParam) const;

    private:
        std::string mQueryString;
        std::vector<Param> mParameters;
        bool mReturnsResultSet;
        bool mRequiresCommit;
        Database& mDatabase;
};
};
}

#include "DatabaseStoredProcedure.inl"

#undef STORED_PROCEDURE_CTOR


#endif // TYPETWO_DATABASESTOREDPROCEDURE_HPP

