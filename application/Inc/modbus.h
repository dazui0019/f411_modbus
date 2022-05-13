#ifndef MODBUS_H
#define MODBUS_H

#include "hicode.h"

typedef enum
{
    MODBUS_OK       = 0x00U,
    ID_ERROR        = 0x01U,
    CODE_ERROR      = 0x02U,
    CRC_ERROR       = 0x03U,
    GENERAL_ERROR   = 0x04U
} MODBUS_ERROR;

class modbus{
public:
    explicit modbus(uint8_t* recBuffer){
        Buffer = recBuffer;
    }
    uint8_t* Buffer;    //modbusΩ” ’ª∫≥Â
    MODBUS_ERROR Modbus_ReceiveHandler(sensor&) const;
    static MODBUS_ERROR Modbus_Transmit(sensor&);
    static uint16_t crc16(uint8_t *buffer, uint16_t buffer_length);
private:
};
#endif
