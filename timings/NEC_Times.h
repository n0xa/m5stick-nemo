#ifndef _NEC_TIMES_H_
#define _NEC_TIMES_H_

#define NEC_AGC_LEN 900
#define NEC_LONG_PAUSE_LEN 450
#define NEC_PULSE_LEN 56
#define NEC_LOGIC_ONE_LEN 169
#define NEC_LOGIC_ZERO_LEN 56
#define NEC_NUM_OF_PAIRS 34
#define NEC_NUM_OF_BITS_PER_INDEX 2

#define NEC_CARRIER_FREQ 38000

/*
** INDEX #		    PWM ON		OFF
** 0 (LOGIC 0)	    0.56ms		0.56ms
** 1 (LOGIC 1)	    0.56ms		1.69ms
** 2 (AGC-PAUSE)	9ms		    4.5ms
** 3 (STOP)	        0.56ms		0ms
*/
const uint16_t NEC_Times[] PROGMEM = {
    NEC_PULSE_LEN, NEC_LOGIC_ZERO_LEN, // 0.56ms on 0.56ms off (logic 0)
    NEC_PULSE_LEN, NEC_LOGIC_ONE_LEN,  // 0.56ms on 1.69ms off (logic 1)
    NEC_AGC_LEN, NEC_LONG_PAUSE_LEN, // 9ms on 4.5ms off (AGC-LPAUSE)
    NEC_PULSE_LEN, 0,                  // 0.56ms on 0ms off (stop)
};

#endif