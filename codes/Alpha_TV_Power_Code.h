#ifndef _ALPHA_TV_POWER_CODE_H_
#define _ALPHA_TV_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/NEC_Times.h"

#define CODE_ALPHA_FREQ 38000

const uint8_t code_AlphaCodes[] PROGMEM = {
    0x80,
    0x00,
    0x15,
    0x55,
    0x11,
    0x10,
    0x04,
    0x45,
    0x70,
};

const struct IrCode code_AlphaCode PROGMEM = {
    freq_to_timerval(CODE_ALPHA_FREQ),
    NEC_NUM_OF_PAIRS,          // # of pairs
    NEC_NUM_OF_BITS_PER_INDEX, // # of bits per index
    NEC_Times,
    code_AlphaCodes
};

#endif