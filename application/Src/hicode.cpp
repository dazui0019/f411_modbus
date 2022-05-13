#include "main.h"
#include "hicode.h"
#include "modbus.h"
#include "retarget.h"

void sensor::Function_03_Handler(const uint8_t recBuffer[], sensor& soil)
{
    soil.temperature = ((recBuffer[0] << 8)|recBuffer[1])/10.0F;
    soil.moisture = ((recBuffer[2]<<8)|recBuffer[3])/10;
}

void sensor::structure_traMsg(){
    uint16_t crc16;
    mb_message[0] = ID;
    crc16 = modbus::crc16(mb_message ,6);
    mb_message[6] = (uint8_t)((crc16 & 0xFF00)>>8);
    mb_message[7] = (uint8_t)(crc16 & 0x00FF);
}
