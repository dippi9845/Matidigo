#include "port.h"
using namespace matidigo::types;


matidigo::hardware::Port::Port(uint16_t portnumber)
{
    this->portnumber = portnumber;
}

matidigo::hardware::Port::~Port()
{
}



matidigo::hardware::Port8Bit::Port8Bit(uint16_t portnumber)
    : Port(portnumber)
{
}

matidigo::hardware::Port8Bit::~Port8Bit()
{
}

void matidigo::hardware::Port8Bit::Write(uint8_t data)
{
    Write8(portnumber, data);
}

uint8_t matidigo::hardware::Port8Bit::Read()
{
    return Read8(portnumber);
}



matidigo::hardware::Port8BitSlow::Port8BitSlow(uint16_t portnumber)
    : Port8Bit(portnumber) {
}

matidigo::hardware::Port8BitSlow::~Port8BitSlow() {
}

void matidigo::hardware::Port8BitSlow::Write(uint8_t data) {
    Write8Slow(portnumber, data);
}


matidigo::hardware::Port16Bit::Port16Bit(uint16_t portnumber)
    : Port(portnumber)
{
}

matidigo::hardware::Port16Bit::~Port16Bit() {
}

void matidigo::hardware::Port16Bit::Write(uint16_t data)
{
    Write16(portnumber, data);
}

uint16_t matidigo::hardware::Port16Bit::Read()
{
    return Read16(portnumber);
}





Port32Bit::Port32Bit(uint16_t portnumber)
    : Port(portnumber)
{
}

Port32Bit::~Port32Bit()
{
}

void Port32Bit::Write(uint32_t data)
{
    Write32(portnumber, data);
}

uint32_t Port32Bit::Read()
{
    return Read32(portnumber);
}