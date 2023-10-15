 
#ifndef __MATIDIGO__NET__ARP_H
#define __MATIDIGO__NET__ARP_H


#include "../types.h"
#include "etherframe.h"


namespace matidigo
{
    namespace net
    {
        
        struct AddressResolutionProtocolMessage
        {
            types::uint16_t hardwareType;
            types::uint16_t protocol;
            types::uint8_t hardwareAddressSize; // 6
            types::uint8_t protocolAddressSize; // 4
            types::uint16_t command;
            

            types::uint64_t srcMAC : 48;
            types::uint32_t srcIP;
            types::uint64_t dstMAC : 48;
            types::uint32_t dstIP;
            
        } __attribute__((packed));
        
        
        
        class AddressResolutionProtocol : public EtherFrameHandler
        {
            
            types::uint32_t IPcache[128];
            types::uint64_t MACcache[128];
            int numCacheEntries;
            
        public:
            AddressResolutionProtocol(EtherFrameProvider* backend);
            ~AddressResolutionProtocol();
            
            bool OnEtherFrameReceived(types::uint8_t* etherframePayload, types::uint32_t size);

            void RequestMACAddress(types::uint32_t IP_BE);
            types::uint64_t GetMACFromCache(types::uint32_t IP_BE);
            types::uint64_t Resolve(types::uint32_t IP_BE);
            void BroadcastMACAddress(types::uint32_t IP_BE);
        };
        
        
    }
}


#endif