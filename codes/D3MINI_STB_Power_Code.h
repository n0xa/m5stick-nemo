#ifndef _D3MINI_STB_POWER_CODE_H_
#define _D3MINI_STB_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/NEC_Times.h"

#define CODE_D3MINISTB_FREQ 38000 

const uint8_t code_D3MINISTBCodes[] PROGMEM = {
    0x85,
    0x00,
    0x14,
    0x55,
    0x45,
    0x40,
    0x10,
    0x15,
    0x70
};

const struct IrCode code_D3MINISTBCode PROGMEM = {
    freq_to_timerval(CODE_D3MINISTB_FREQ),
    NEC_NUM_OF_PAIRS,          // # of pairs
    NEC_NUM_OF_BITS_PER_INDEX, // # of bits per index
    NEC_Times,
    code_D3MINISTBCodes
};

#endif