 
#ifndef __MATIDIGO__NET__UDP_H
#define __MATIDIGO__NET__UDP_H


#include "../types.h"
#include "ipv4.h"
#include "../memory_management.h"

namespace matidigo
{
    namespace net
    {
        
        struct UserDatagramProtocolHeader
        {
            types::uint16_t srcPort;
            types::uint16_t dstPort;
            types::uint16_t length;
            types::uint16_t checksum;
        } __attribute__((packed));
       
      
      
        class UserDatagramProtocolSocket;
        class UserDatagramProtocolProvider;
        
        
        
        class UserDatagramProtocolHandler
        {
        public:
            UserDatagramProtocolHandler();
            ~UserDatagramProtocolHandler();
            virtual void HandleUserDatagramProtocolMessage(UserDatagramProtocolSocket* socket, types::uint8_t* data, types::uint16_t size);
        };
      
        
      
        class UserDatagramProtocolSocket
        {
        friend class UserDatagramProtocolProvider;
        protected:
            types::uint16_t remotePort;
            types::uint32_t remoteIP;
            types::uint16_t localPort;
            types::uint32_t localIP;
            UserDatagramProtocolProvider* backend;
            UserDatagramProtocolHandler* handler;
            bool listening;
        public:
            UserDatagramProtocolSocket(UserDatagramProtocolProvider* backend);
            ~UserDatagramProtocolSocket();
            virtual void HandleUserDatagramProtocolMessage(types::uint8_t* data, types::uint16_t size);
            virtual void Send(types::uint8_t* data, types::uint16_t size);
            virtual void Disconnect();
        };
      
      
        class UserDatagramProtocolProvider : InternetProtocolHandler
        {
        protected:
            UserDatagramProtocolSocket* sockets[65535];
            types::uint16_t numSockets;
            types::uint16_t freePort;
            
        public:
            UserDatagramProtocolProvider(InternetProtocolProvider* backend);
            ~UserDatagramProtocolProvider();
            
            virtual bool OnInternetProtocolReceived(types::uint32_t srcIP_BE, types::uint32_t dstIP_BE,
                                                    types::uint8_t* internetprotocolPayload, types::uint32_t size);

            virtual UserDatagramProtocolSocket* Connect(types::uint32_t ip, types::uint16_t port);
            virtual UserDatagramProtocolSocket* Listen(types::uint16_t port);
            virtual void Disconnect(UserDatagramProtocolSocket* socket);
            virtual void Send(UserDatagramProtocolSocket* socket, types::uint8_t* data, types::uint16_t size);

            virtual void Bind(UserDatagramProtocolSocket* socket, UserDatagramProtocolHandler* handler);
        };
        
        
    }
}



#endif