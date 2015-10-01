///////////////////////////////////
// TypeTwo internal headers
#include "DatabaseStream.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <iostream>
#include <sstream>
///////////////////////////////////

///////////////////////////////////
// OTL4
#define OTL_ODBC
#include "otlv4.h"
///////////////////////////////////

DatabaseStream::DatabaseStream(otl_stream* stream)
: mStream(*stream)
{
}

///////////////////////////////////

DatabaseStream::~DatabaseStream()
{
    delete &mStream;
}

///////////////////////////////////

std::string DatabaseStream::getFetchDataProtocolString()
{
    try
    {
        std::stringstream stream;
        int numColumns;
        otl_column_desc* columns = mStream.describe_select(numColumns);
        for(int i = 0; i < numColumns - 1; i++)
            stream << columns[i].dbtype << ' ' << columns[i].name << ',';

        stream << columns[numColumns - 1].dbtype << ' ' << columns[numColumns - 1].name;

        char* buffer = new char(100);
        try
        {
            while(!mStream.eof())
            {
                mStream >> buffer;
                stream << '\n' << buffer;
            }
        }
        catch(otl_exception& e)
        {
            std::cout   << "Invalid use of DatabaseStream::getFetchDataProtocolString function. To use this function, the stored procedure "
                        << "from where this DatabaseStream object was fetched from must be called (DatabaseStoredProcedure::call) with the toString parameter set to true."
                        << std::endl;

            throw;
        }

        return stream.str();
    }
    catch(otl_exception& e)
    {
        std::cout << "Database error: " << e.msg << std::endl;
    }
}

///////////////////////////////////

otl_stream& DatabaseStream::getOtlStream()
{
    return mStream;
}

