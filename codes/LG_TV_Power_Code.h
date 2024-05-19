#ifndef _LG_TV_POWER_CODE_H_
#define _LG_TV_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/NEC_Times.h"

#define CODE_LG_FREQ 38000 // for this freq_to_timerval my tvbgone does 38.0952khz

const uint8_t code_LGCodes[] PROGMEM = {
    0x81,
    0x00,
    0x14,
    0x55,
    0x40,
    0x40,
    0x15,
    0x15,
    0x70
};

const struct IrCode code_LGCode PROGMEM = {
    freq_to_timerval(CODE_LG_FREQ),
    NEC_NUM_OF_PAIRS,          // # of pairs
    NEC_NUM_OF_BITS_PER_INDEX, // # of bits per index
    NEC_Times,
    code_LGCodes
};

#endif