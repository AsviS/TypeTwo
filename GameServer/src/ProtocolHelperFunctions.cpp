///////////////////////////////////
// TypeTwo internal headers
#include "ProtocolHelperFunctions.hpp"
///////////////////////////////////

std::string getClientIp(libwebsocket_context* context, libwebsocket* wsi)
{
    unsigned int BUFFER_SIZE = 50;
    char* ipBuffer = new char[BUFFER_SIZE];
    memset(ipBuffer, 0, BUFFER_SIZE);

    libwebsockets_get_peer_addresses(context, wsi, libwebsocket_get_socket_fd(wsi), ipBuffer, 0, ipBuffer, BUFFER_SIZE);

	std::string ip(ipBuffer);
	delete[] ipBuffer;

	return ip;
}

#include <iostream>
char* stringToChar(const std::string& str)
{
	char* cArray = new char[str.size() + 1];

	#if (_MSC_VER >= 1400)
	#pragma warning(push)
	#pragma warning(disable: 4996)
	#endif 
	str.copy(cArray, str.size());
	#if (_MSC_VER >= 1400)
	#pragma warning(pop) 
	#endif
	cArray[str.size()] = '\0';
	std::cout << cArray << std::endl;
	return cArray;
}

unsigned char* stringToUChar(const std::string& str)
{
	return (unsigned char*)stringToChar(str);
}