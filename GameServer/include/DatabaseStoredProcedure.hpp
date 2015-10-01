#ifndef TYPETWO_DATABASESTOREDPROCEDURE_HPP
#define TYPETWO_DATABASESTOREDPROCEDURE_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "DatabaseConnections.hpp"
#include "DatabaseStream.hpp"
#include "DatabaseStoredProcedureParameter.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <vector>
#include <memory>
///////////////////////////////////


template<typename... Params>
class DatabaseStoredProcedure
{
    public:
        typedef DatabaseStoredProcedureParameter Param;

        DatabaseStoredProcedure(std::string name, std::vector<Param> parameters, bool returnsResultSet = false, bool requiresCommit = false, Database& database = DatabaseConnections::DEFAULT);


        std::unique_ptr<DatabaseStream> call(Params... params, bool toString = false) const;

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

#include "DatabaseStoredProcedure.inl"

#endif // TYPETWO_DATABASESTOREDPROCEDURE_HPP

