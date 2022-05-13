#ifndef HI_CODE_H
#define HI_CODE_H

#include "main.h"

class sensor{
public:
    explicit sensor(uint8_t slaveID){
        ID = slaveID;
    }
    static void Function_03_Handler(const uint8_t recBuffer[], sensor&);
    void structure_traMsg();

    uint8_t ID;
    float temperature = 0;
    int moisture = 0;
    //                        ID        CODE      reg_h     reg_l     count_h   count_l   crc_h     crc_l
    uint8_t mb_message[8] = {0x00, 0x03, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00};
private:
};

#endif