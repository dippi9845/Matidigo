 
#ifndef __MATIDIGO__NET__ETHERFRAME_H
#define __MATIDIGO__NET__ETHERFRAME_H


#include "../types.h"
#include "../drivers/amd_am79c973.h"
#include "../memory_management.h"


namespace matidigo
{
    namespace net
    {
        
        struct EtherFrameHeader
        {
            types::uint64_t dstMAC_BE : 48;
            types::uint64_t srcMAC_BE : 48;
            types::uint16_t etherType_BE;
        } __attribute__ ((packed));
        
        typedef types::uint32_t EtherFrameFooter;
        
        
        
        class EtherFrameProvider;
        
        class EtherFrameHandler
        {
        protected:
            EtherFrameProvider* backend;
            types::uint16_t etherType_BE;
             
        public:
            EtherFrameHandler(EtherFrameProvider* backend, types::uint16_t etherType);
            ~EtherFrameHandler();
            
            virtual bool OnEtherFrameReceived(types::uint8_t* etherframePayload, types::uint32_t size);
            void Send(types::uint64_t dstMAC_BE, types::uint8_t* etherframePayload, types::uint32_t size);
            types::uint32_t GetIPAddress();
        };
        
        
        class EtherFrameProvider : public matidigo::drivers::RawDataHandler
        {
        friend class EtherFrameHandler;
        protected:
            EtherFrameHandler* handlers[65535];
        public:
            EtherFrameProvider(drivers::amd_am79c973* backend);
            ~EtherFrameProvider();
            
            bool OnRawDataReceived(types::uint8_t* buffer, types::uint32_t size);
            void Send(types::uint64_t dstMAC_BE, types::uint16_t etherType_BE, types::uint8_t* buffer, types::uint32_t size);
            
            types::uint64_t GetMACAddress();
            types::uint32_t GetIPAddress();
        };
        
        
        
    }
}



#endif
