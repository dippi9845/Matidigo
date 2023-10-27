 
#ifndef __MATIDIGO__NET__ICMP_H
#define __MATIDIGO__NET__ICMP_H

#include "../types.h"
#include "ipv4.h"


namespace matidigo
{
    namespace net
    {
        
        
        struct InternetControlMessageProtocolMessage
        {
            types::uint8_t type;
            types::uint8_t code;
            
            types::uint16_t checksum;
            types::uint32_t data;

        } __attribute__((packed));
        
        class InternetControlMessageProtocol : InternetProtocolHandler
        {
        public:
            InternetControlMessageProtocol(InternetProtocolProvider* backend);
            ~InternetControlMessageProtocol();
            
            bool OnInternetProtocolReceived(types::uint32_t srcIP_BE, types::uint32_t dstIP_BE,
                                            types::uint8_t* internetprotocolPayload, types::uint32_t size);
            void RequestEchoReply(types::uint32_t ip_be);
        };
        
        
    }
}


#endif