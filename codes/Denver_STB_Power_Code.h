#ifndef _DENVER_STB_POWER_CODE_H_
#define _DENVER_STB_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/NEC_Times.h"

#define CODE_DENVERSTB_FREQ 38000

const uint8_t code_DenverSTBCodes[] PROGMEM = {
    0x80,
    0x00,
    0x15,
    0x54,
    0x50,
    0x51,
    0x05,
    0x04,
    0x70,
};

const struct IrCode code_DenverSTBCode PROGMEM = {
    freq_to_timerval(CODE_DENVERSTB_FREQ),
    NEC_NUM_OF_PAIRS,          // # of pairs
    NEC_NUM_OF_BITS_PER_INDEX, // # of bits per index
    NEC_Times,
    code_DenverSTBCodes
};

#endif