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

namespace Database
{
namespace Stream
{
namespace Standard
{
    template<typename Procedure>
    class Stream
    {
        public:
            Stream(const Procedure& procedure);

            template<typename... ParamTypes>
            void execute(ParamTypes... params);

            template<typename RowType, typename... ParamTypes>
            std::vector<RowType> execute(ParamTypes... params);

        private:
            const Procedure& mProcedure;
            StoredProcedure::StreamPtr mStream;
    };

    template<typename Procedure>
    Stream<Procedure> create(const Procedure& procedure);

    #include "Database/StreamStandard.inl"
}}}


#endif // TYPETWO_DATABASE_STREAM_STANDARD_HPP

