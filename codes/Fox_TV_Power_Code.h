#ifndef _FOX_TV_POWER_CODE_H_
#define _FOX_TV_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/NEC_Times.h"

#define CODE_FOX_FREQ 37800 // for this freq_to_timerval my tvbgone does 38.0952khz

const uint8_t code_FoxCodes[] PROGMEM = {
    0x80,
    0x00,
    0x15,
    0x55,
    0x04,
    0x40,
    0x11,
    0x15,
    0x70,
};

const struct IrCode code_FoxCode PROGMEM = {
    freq_to_timerval(CODE_FOX_FREQ),
    NEC_NUM_OF_PAIRS,          // # of pairs
    NEC_NUM_OF_BITS_PER_INDEX, // # of bits per index
    NEC_Times,
    code_FoxCodes
};

#endif