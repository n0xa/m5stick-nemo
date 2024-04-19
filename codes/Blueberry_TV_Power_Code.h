#ifndef _BLUEBERRY_TV_POWER_CODE_H_
#define _BLUEBERRY_TV_POWER_CODE_H_

#include "../tvbg.h"
#include "../timings/NEC_Times.h"

#define CODE_BLUEBERRY_FREQ 38000

const uint8_t code_BlueberryCodes[] PROGMEM = {
    0x80,
    0x04,
    0x15,
    0x51,
    0x44,
    0x11,
    0x11,
    0x44,
    0x70
};

const struct IrCode code_BlueberryCode PROGMEM = {
    freq_to_timerval(CODE_BLUEBERRY_FREQ),
    NEC_NUM_OF_PAIRS,          // # of pairs
    NEC_NUM_OF_BITS_PER_INDEX, // # of bits per index
    NEC_Times,
    code_BlueberryCodes
};

#endif