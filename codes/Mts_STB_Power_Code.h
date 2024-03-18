#ifndef _MTS_STB_POWER_CODE_H_
#define _MTS_STB_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/NEC_Times.h"

#define CODE_MTSSTB_FREQ 40000

const uint8_t code_MtsSTBCodes[] PROGMEM = {
    0x94,
    0x14,
    0x41,
    0x41,
    0x01,
    0x51,
    0x54,
    0x04,
    0x30,
};

const struct IrCode code_MtsSTBCode PROGMEM = {
    freq_to_timerval(CODE_MTSSTB_FREQ),
    NEC_NUM_OF_PAIRS,          // # of pairs
    NEC_NUM_OF_BITS_PER_INDEX, // # of bits per index
    NEC_Times,
    code_MtsSTBCodes
};

#endif