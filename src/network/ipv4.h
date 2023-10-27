#ifndef __MATIDIGO__NET__IPV4_H
#define __MATIDIGO__NET__IPV4_H

#include "../types.h"
#include "etherframe.h"
#include "arp.h"

namespace matidigo
{
    namespace net
    {
        
        
        struct InternetProtocolV4Message
        {
            types::uint8_t headerLength : 4;
            types::uint8_t version : 4;
            types::uint8_t tos;
            types::uint16_t totalLength;
            
            types::uint16_t ident;
            types::uint16_t flagsAndOffset;
            
            types::uint8_t timeToLive;
            types::uint8_t protocol;
            types::uint16_t checksum;
            
            types::uint32_t srcIP;
            types::uint32_t dstIP;
        } __attribute__((packed));
        
        
        
        class InternetProtocolProvider;
     
        class InternetProtocolHandler
        {
        protected:
            InternetProtocolProvider* backend;
            types::uint8_t ip_protocol;
             
        public:
            InternetProtocolHandler(InternetProtocolProvider* backend, types::uint8_t protocol);
            ~InternetProtocolHandler();
            
            virtual bool OnInternetProtocolReceived(types::uint32_t srcIP_BE, types::uint32_t dstIP_BE,
                                            types::uint8_t* internetprotocolPayload, types::uint32_t size);
            void Send(types::uint32_t dstIP_BE, types::uint8_t* internetprotocolPayload, types::uint32_t size);
        };
     
     
        class InternetProtocolProvider : public EtherFrameHandler
        {
        friend class InternetProtocolHandler;
        protected:
            InternetProtocolHandler* handlers[255];
            AddressResolutionProtocol* arp;
            types::uint32_t gatewayIP;
            types::uint32_t subnetMask;
            
        public:
            InternetProtocolProvider(EtherFrameProvider* backend, 
                                     AddressResolutionProtocol* arp,
                                     types::uint32_t gatewayIP, types::uint32_t subnetMask);
            ~InternetProtocolProvider();
            
            bool OnEtherFrameReceived(types::uint8_t* etherframePayload, types::uint32_t size);

            void Send(types::uint32_t dstIP_BE, types::uint8_t protocol, types::uint8_t* buffer, types::uint32_t size);
            
            static types::uint16_t Checksum(types::uint16_t* data, types::uint32_t lengthInBytes);
        };
    }
}


#endif
