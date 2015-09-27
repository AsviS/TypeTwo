///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
#include "WebSocketSubProtocols.hpp"
#include "WebSocketServer.hpp"
#include "UserProvider.hpp"
#include "UnitProvider.hpp"
#include "DatabaseConnections.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <iostream>
#include <sstream>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
///////////////////////////////////

const WebSocketSubProtocol& WebSocketSubProtocols::FETCH_DATA = WebSocketSubProtocol
(
    "fetch-data",
    sizeof(WebSocketConnection*),
    [](libwebsocket_context* context,
                   libwebsocket* webSocketInstance,
                   libwebsocket_callback_reasons reason,
                   void* connectionData,
                   void *messageData,
                   size_t messageLength)
    {
        /////////////////////////////////
        // Always call the standard protocol
        WebSocketSubProtocol::Result result = WebSocketSubProtocol::performStandardProtocol(context, webSocketInstance, reason, connectionData);
        if(result == WebSocketSubProtocol::Result::Fail)
            return (int)result;
        /////////////////////////////////

        if(reason == LWS_CALLBACK_ESTABLISHED)//RECEIVE)
        {
            //std::string message = WebSocketSubProtocol::messageToString(messageData, messageLength);

            //if(message == "get-units")
            {
                WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);

                UnitProvider unitProvider(DatabaseConnections::DEFAULT);
                std::vector<UnitType> unitTypes = unitProvider.getUnitTypes();

                UserProvider userProvider(DatabaseConnections::DEFAULT);
                std::vector<Unit> units = unitProvider.getUnits(userProvider.getId(connection.getUsername()));

                std::stringstream output;
                output  << "You have the following units: " << std::endl
                        << "Total: " << units.size() << std::endl
                        << std::endl;

                for(int i = 0; i < units.size(); i++)
                {
                    Unit unit = units[i];
                    UnitType type = unitTypes[unit.unitTypeId - 1];

                    output  << "Unit " << i << ": " << std::endl
                            << "\tType: " <<  type.name << std::endl
                            << "\tHP: " << unit.hp << "/" << type.maxHp << std::endl
                            << "\tDamage: " << type.damage << std::endl
                            << "\tMovement speed: " << type.movementSpeed << std::endl
                            << "\tAttack range: " << type.attackRange << std::endl
                            << "\tAttack speed: " << type.attackSpeed << std::endl
                            << std::endl;
                }

                WebSocketSubProtocol::getConnection(connectionData).sendString(output.str());
            }
        }

        return 0;
    }
);
