#ifndef TYPETWO_DATABASESTREAM_HPP
#define TYPETWO_DATABASESTREAM_HPP

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

///////////////////////////////////
// OTL4
class otl_stream;
///////////////////////////////////

class DatabaseStream
{
    public:
        DatabaseStream(otl_stream* stream);

        ~DatabaseStream();

        std::string getFetchDataProtocolString();
        otl_stream& getOtlStream();

    private:
        otl_stream& mStream;
};

#endif // TYPETWO_DATABASESTREAM_HPP

