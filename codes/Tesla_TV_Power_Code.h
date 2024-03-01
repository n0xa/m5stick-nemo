#ifndef _TESLA_TV_POWER_CODE_H_
#define _TESLA_TV_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/RCA_Times.h"

#define CODE_TESLA_FREQ 38000

const uint8_t code_TeslaCodes[] PROGMEM = {
    0x95,
    0x01,
    0x11,
    0x00,
    0x54,
    0x44,
    0x70
};

const struct IrCode code_TeslaCode PROGMEM = {
    freq_to_timerval(CODE_TESLA_FREQ),
    RCA_NUM_OF_PAIRS,          // # of pairs
    RCA_NUM_OF_BITS_PER_INDEX, // # of bits per index
    RCA_Times,
    code_TeslaCodes
};

#endif