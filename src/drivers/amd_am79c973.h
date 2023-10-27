 
#ifndef __MATIDIGO__DRIVERS__AMD_AM79C973_H
#define __MATIDIGO__DRIVERS__AMD_AM79C973_H


#include "driver.h"

#include "../types.h"

#include "../hardware/pci.h"
#include "../hardware/interrupts.h"
#include "../hardware/port.h"


namespace matidigo
{
    namespace drivers
    {
        
        class amd_am79c973;
        
        class RawDataHandler
        {
        protected:
            amd_am79c973* backend;
        public:
            RawDataHandler(amd_am79c973* backend);
            ~RawDataHandler();
            
            virtual bool OnRawDataReceived(matidigo::types::uint8_t* buffer, matidigo::types::uint32_t size);
            void Send(matidigo::types::uint8_t* buffer, matidigo::types::uint32_t size);
        };
        
        
        class amd_am79c973 : public Driver, public hardware::InterruptHandler
        {
            struct InitializationBlock
            {
                matidigo::types::uint16_t mode;
                unsigned reserved1 : 4;
                unsigned numSendBuffers : 4;
                unsigned reserved2 : 4;
                unsigned numRecvBuffers : 4;
                matidigo::types::uint64_t physicalAddress : 48;
                matidigo::types::uint16_t reserved3;
                matidigo::types::uint64_t logicalAddress;
                matidigo::types::uint32_t recvBufferDescrAddress;
                matidigo::types::uint32_t sendBufferDescrAddress;
            } __attribute__((packed));
            
            
            struct BufferDescriptor
            {
                matidigo::types::uint32_t address;
                matidigo::types::uint32_t flags;
                matidigo::types::uint32_t flags2;
                matidigo::types::uint32_t avail;
            } __attribute__((packed));
            
            hardware::Port16Bit MACAddress0Port;
            hardware::Port16Bit MACAddress2Port;
            hardware::Port16Bit MACAddress4Port;
            hardware::Port16Bit registerDataPort;
            hardware::Port16Bit registerAddressPort;
            hardware::Port16Bit resetPort;
            hardware::Port16Bit busControlRegisterDataPort;
            
            InitializationBlock initBlock;
            
            
            BufferDescriptor* sendBufferDescr;
            matidigo::types::uint8_t sendBufferDescrMemory[2048+15];
            matidigo::types::uint8_t sendBuffers[2*1024+15][8];
            matidigo::types::uint8_t currentSendBuffer;
            
            BufferDescriptor* recvBufferDescr;
            matidigo::types::uint8_t recvBufferDescrMemory[2048+15];
            matidigo::types::uint8_t recvBuffers[2*1024+15][8];
            matidigo::types::uint8_t currentRecvBuffer;
            
            
            RawDataHandler* handler;
            
        public:
            amd_am79c973(matidigo::hardware::PeripheralComponentInterconnectDeviceDescriptor *dev,
                         matidigo::hardware::InterruptManager* interrupts);
            ~amd_am79c973();
            
            void Activate();
            int Reset();
            matidigo::types::uint32_t HandleInterrupt(matidigo::types::uint32_t esp);
            
            void Send(matidigo::types::uint8_t* buffer, int count);
            void Receive();
            
            void SetHandler(RawDataHandler* handler);
            matidigo::types::uint64_t GetMACAddress();
            void SetIPAddress(matidigo::types::uint32_t);
            matidigo::types::uint32_t GetIPAddress();
        };
        
        
        
    }
}



#endif
