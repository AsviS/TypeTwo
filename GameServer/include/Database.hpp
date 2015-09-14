#ifndef TYPETWO_DATABASE_HPP
#define TYPETWO_DATABASE_HPP

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

///////////////////////////////////
// OTL4
class otl_connect;
class otl_stream;
///////////////////////////////////



class Database
{
    public:
        Database(std::string host, int port, std::string schema, std::string username, std::string password, std::string driver = "{MySQL ODBC 5.3 ANSI Driver}");
        ~Database();

        otl_connect& getConnection();

    private:
        otl_connect& mConnection;
};
/*
    std::string hashedPassword;
    std::string salt;
    try
    {
        std::string strConn = "DRIVER={MySQL ODBC 5.3 ANSI Driver};SERVER=192.168.1.156;PORT=3306;DATABASE=typetwo;USER=typetwo;PASSWORD=lethal type two diabetes;";
        db.rlogon(strConn.c_str());

        //otl_cursor::direct_exec(db, "drop table temp", otl_exception::disabled);
        //otl_cursor::direct_exec(db, "create table temp(f1 int, f2 varchar(30))");
        otl_stream output(1, "CALL user_get_credentials(:f1<char[17],in>, :f2<char[129],out>, :f3<char[256],out>)", db);
        output.set_commit(0);
        output << "vendrii";
        char* hashedPasswordBuffer = new char[129];
        char* saltBuffer = new char[256];

        output >> hashedPasswordBuffer >> saltBuffer;


        hashedPassword.assign(hashedPasswordBuffer);
        salt.assign(saltBuffer);

        std::cout << "Done." << std::endl;
    }
    catch(otl_exception& e)
    {
        std::cout << e.msg << std::endl;
    }

*/

#endif // TYPETWO_DATABASE_HPP
