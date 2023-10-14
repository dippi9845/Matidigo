#ifndef __MYOS__HARDWARECOMMUNICATION__PORT_H
#define __MYOS__HARDWARECOMMUNICATION__PORT_H

#include "../types.h"
//using namespace matidigo::types;


namespace myos
{
    namespace hardware
    {

        class Port
        {
            protected:
                Port(matidigo::types::uint16_t portnumber);

                
                ~Port();
                matidigo::types::uint16_t portnumber;
        };

        
        class Port8Bit : public Port
        {
            public:
                Port8Bit(matidigo::types::uint16_t portnumber);
                ~Port8Bit();

                virtual matidigo::types::uint8_t Read();
                virtual void Write(matidigo::types::uint8_t data);

            protected:
                static inline matidigo::types::uint8_t Read8(matidigo::types::uint16_t _port)
                {
                    matidigo::types::uint8_t result;
                    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write8(matidigo::types::uint16_t _port, matidigo::types::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port8BitSlow : public Port8Bit
        {
            public:
                Port8BitSlow(matidigo::types::uint16_t portnumber);
                ~Port8BitSlow();

                virtual void Write(matidigo::types::uint8_t data);
            protected:
                static inline void Write8Slow(matidigo::types::uint16_t _port, matidigo::types::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
                }

        };



        class Port16Bit : public Port
        {
            public:
                Port16Bit(matidigo::types::uint16_t portnumber);
                ~Port16Bit();

                virtual matidigo::types::uint16_t Read();
                virtual void Write(matidigo::types::uint16_t data);

            protected:
                static inline matidigo::types::uint16_t Read16(matidigo::types::uint16_t _port)
                {
                    matidigo::types::uint16_t result;
                    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write16(matidigo::types::uint16_t _port, matidigo::types::uint16_t _data)
                {
                    __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port32Bit : public Port
        {
            public:
                Port32Bit(matidigo::types::uint16_t portnumber);
                ~Port32Bit();

                virtual matidigo::types::uint32_t Read();
                virtual void Write(matidigo::types::uint32_t data);

            protected:
                static inline matidigo::types::uint32_t Read32(matidigo::types::uint16_t _port)
                {
                    matidigo::types::uint32_t result;
                    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write32(matidigo::types::uint16_t _port, matidigo::types::uint32_t _data)
                {
                    __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
                }
        };

    }
}


#endif