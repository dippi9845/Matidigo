#ifndef __MATIDIGO__HARDWARE__PCI_H
#define __MATIDIGO__HARDWARE__PCI_H

#include "port.h"
#include "interrupts.h"

#include "../types.h"
#include "../memory_management.h"

#include "../drivers/driver.h"

namespace matidigo
{
    namespace hardware
    {

        enum BaseAddressRegisterType
        {
            MemoryMapping = 0,
            InputOutput = 1
        };
        
        
        
        class BaseAddressRegister
        {
        public:
            bool prefetchable;
            matidigo::types::uint8_t* address;
            matidigo::types::uint32_t size;
            BaseAddressRegisterType type;
        };
        
        
        
        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            matidigo::types::uint32_t portBase;
            matidigo::types::uint32_t interrupt;
            
            matidigo::types::uint16_t bus;
            matidigo::types::uint16_t device;
            matidigo::types::uint16_t function;

            matidigo::types::uint16_t vendor_id;
            matidigo::types::uint16_t device_id;
            
            matidigo::types::uint8_t class_id;
            matidigo::types::uint8_t subclass_id;
            matidigo::types::uint8_t interface_id;

            matidigo::types::uint8_t revision;
            
            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();
            
        };


        class PeripheralComponentInterconnectController
        {
            Port32Bit dataPort;
            Port32Bit commandPort;
            
        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();
            
            matidigo::types::uint32_t Read(matidigo::types::uint16_t bus, matidigo::types::uint16_t device, matidigo::types::uint16_t function, matidigo::types::uint32_t registeroffset);
            
            void Write(matidigo::types::uint16_t bus, matidigo::types::uint16_t device, matidigo::types::uint16_t function, matidigo::types::uint32_t registeroffset, matidigo::types::uint32_t value);
            
            bool DeviceHasFunctions(matidigo::types::uint16_t bus, matidigo::types::uint16_t device);
            
            void SelectDrivers(matidigo::drivers::DriverManager* driverManager, matidigo::hardware::InterruptManager* interrupts);

            matidigo::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, matidigo::hardware::InterruptManager* interrupts);

            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(matidigo::types::uint16_t bus, matidigo::types::uint16_t device, matidigo::types::uint16_t function);

            BaseAddressRegister GetBaseAddressRegister(matidigo::types::uint16_t bus, matidigo::types::uint16_t device, matidigo::types::uint16_t function, matidigo::types::uint16_t bar);
        };

    }
}
    
#endif