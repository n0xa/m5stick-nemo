#ifndef _VOX_TV_POWER_CODE_H_
#define _VOX_TV_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/NEC_Times.h"

#define CODE_VOX_FREQ 38000

const uint8_t code_VoxCodes[] PROGMEM = {
    0x80,
    0x01,
    0x15,
    0x54,
    0x54,
    0x40,
    0x01,
    0x15,
    0x70,
};

const struct IrCode code_VoxCode PROGMEM = {
    freq_to_timerval(CODE_VOX_FREQ),
    NEC_NUM_OF_PAIRS,          // # of pairs
    NEC_NUM_OF_BITS_PER_INDEX, // # of bits per index
    NEC_Times,
    code_VoxCodes
};

#endif