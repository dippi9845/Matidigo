#ifndef __MATIDIGO__NET__TCP_H
#define __MATIDIGO__NET__TCP_H


#include "../types.h"
#include "ipv4.h"
#include "../memory_management.h"


namespace matidigo
{
    namespace net
    {
        
        
        enum TransmissionControlProtocolSocketState
        {
            CLOSED,
            LISTEN,
            SYN_SENT,
            SYN_RECEIVED,
            
            ESTABLISHED,
            
            FIN_WAIT1,
            FIN_WAIT2,
            CLOSING,
            TIME_WAIT,
            
            CLOSE_WAIT
            //LAST_ACK
        };
        
        enum TransmissionControlProtocolFlag
        {
            FIN = 1,
            SYN = 2,
            RST = 4,
            PSH = 8,
            ACK = 16,
            URG = 32,
            ECE = 64,
            CWR = 128,
            NS = 256
        };
        
        
        struct TransmissionControlProtocolHeader
        {
            types::uint16_t srcPort;
            types::uint16_t dstPort;
            types::uint32_t sequenceNumber;
            types::uint32_t acknowledgementNumber;
            
            types::uint8_t reserved : 4;
            types::uint8_t headerSize32 : 4;
            types::uint8_t flags;
            
            types::uint16_t windowSize;
            types::uint16_t checksum;
            types::uint16_t urgentPtr;
            
            types::uint32_t options;
        } __attribute__((packed));
       
      
        struct TransmissionControlProtocolPseudoHeader
        {
            types::uint32_t srcIP;
            types::uint32_t dstIP;
            types::uint16_t protocol;
            types::uint16_t totalLength;
        } __attribute__((packed));
      
      
        class TransmissionControlProtocolSocket;
        class TransmissionControlProtocolProvider;
        
        
        
        class TransmissionControlProtocolHandler
        {
        public:
            TransmissionControlProtocolHandler();
            ~TransmissionControlProtocolHandler();
            virtual bool HandleTransmissionControlProtocolMessage(TransmissionControlProtocolSocket* socket, types::uint8_t* data, types::uint16_t size);
        };
      
        
      
        class TransmissionControlProtocolSocket
        {
        friend class TransmissionControlProtocolProvider;
        protected:
            types::uint16_t remotePort;
            types::uint32_t remoteIP;
            types::uint16_t localPort;
            types::uint32_t localIP;
            types::uint32_t sequenceNumber;
            types::uint32_t acknowledgementNumber;

            TransmissionControlProtocolProvider* backend;
            TransmissionControlProtocolHandler* handler;
            
            TransmissionControlProtocolSocketState state;
        public:
            TransmissionControlProtocolSocket(TransmissionControlProtocolProvider* backend);
            ~TransmissionControlProtocolSocket();
            virtual bool HandleTransmissionControlProtocolMessage(types::uint8_t* data, types::uint16_t size);
            virtual void Send(types::uint8_t* data, types::uint16_t size);
            virtual void Disconnect();
        };
      
      
        class TransmissionControlProtocolProvider : InternetProtocolHandler
        {
        protected:
            TransmissionControlProtocolSocket* sockets[65535];
            types::uint16_t numSockets;
            types::uint16_t freePort;
            
        public:
            TransmissionControlProtocolProvider(InternetProtocolProvider* backend);
            ~TransmissionControlProtocolProvider();
            
            virtual bool OnInternetProtocolReceived(types::uint32_t srcIP_BE, types::uint32_t dstIP_BE,
                                                    types::uint8_t* internetprotocolPayload, types::uint32_t size);

            virtual TransmissionControlProtocolSocket* Connect(types::uint32_t ip, types::uint16_t port);
            virtual void Disconnect(TransmissionControlProtocolSocket* socket);
            virtual void Send(TransmissionControlProtocolSocket* socket, types::uint8_t* data, types::uint16_t size,
                              types::uint16_t flags = 0);

            virtual TransmissionControlProtocolSocket* Listen(types::uint16_t port);
            virtual void Bind(TransmissionControlProtocolSocket* socket, TransmissionControlProtocolHandler* handler);
        };
        
        
        
        
    }
}


#endif
