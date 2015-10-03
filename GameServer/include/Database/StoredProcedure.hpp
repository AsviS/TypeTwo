#ifndef TYPETWO_DATABASE_STORED_PROCEDURE_HPP
#define TYPETWO_DATABASE_STORED_PROCEDURE_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "Database/Connections.hpp"
#include "Database/StoredProcedureParameter.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <vector>
#include <memory>
///////////////////////////////////

#define DATABASE_STORED_PROCEDURE_PARAMS(...) __VA_ARGS__
#define DATABASE_STORED_PROCEDURE_RETURNS(...) __VA_ARGS__

#define DATABASE_STORED_PROCEDURE_PARAM(TYPE, DIRECTION) \
Database::StoredProcedureParameter(Database::StoredProcedureParameter::Type::TYPE, Database::StoredProcedureParameter::Direction::P_##DIRECTION)

#define \
DATABASE_STORED_PROCEDURE(NAME, PARAM_TYPES, RETURN_TYPES) \
const Database::StoredProcedure::ParameterTypes<PARAM_TYPES>::ResultSetTypes<RETURN_TYPES> NAME


#define STORED_PROCEDURE_CTOR ResultSetTypes

namespace Database
{
namespace StoredProcedure
{
template<typename... ParamTypes>
struct ParameterTypes
{
template <typename... ResultTypes>
class ResultSetTypes
{
    private:

    public:
        typedef StoredProcedureParameter Param;


        STORED_PROCEDURE_CTOR(std::string name, std::vector<Param> parameters = {}, bool requiresCommit = false, Connection& database = Connections::DEFAULT);

        void call(ParamTypes... params) const;

        template <typename RowType>
        std::vector<RowType> call(ParamTypes... params) const;

        std::string callAsFetchDataProtocol(ParamTypes... params) const;

    private:
        std::string compileQueryString(std::string name, std::vector<Param> parameters);

        template <typename CurrentParam, typename... RemainingParams>
        void executeInputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam currentParam, RemainingParams... remainingParams) const;

        template <typename CurrentParam>
        void executeInputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam currentParam) const;

        void executeInputParameters(otl_stream& stream, unsigned int currentIndex) const;


        template <typename CurrentParam, typename... RemainingParams>
        void executeOutputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam& currentParam, RemainingParams&... remainingParams) const;

        template <typename CurrentParam>
        void executeOutputParameters(otl_stream& stream, unsigned int currentIndex, CurrentParam& currentParam) const;

        void executeOutputParameters(otl_stream& stream, unsigned int currentIndex) const;

    private:
        std::string mQueryString;
        std::vector<Param> mParameters;
        bool mReturnsResultSet;
        bool mRequiresCommit;
        Connection& mDatabase;
};
};
}
}

#include "Database/StoredProcedure.inl"

#undef STORED_PROCEDURE_CTOR


#endif // TYPETWO_DATABASE_STORED_PROCEDURE_HPP

