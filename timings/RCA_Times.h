#ifndef _RCA_TIMES_H_
#define _RCA_TIMES_H_

#define RCA_AGC_LEN 400
#define RCA_LONG_PAUSE_LEN RCA_AGC_LEN
#define RCA_PULSE_LEN 50
#define RCA_LOGIC_ONE_LEN 200
#define RCA_LOGIC_ZERO_LEN 100
#define RCA_NUM_OF_PAIRS 26
#define RCA_NUM_OF_BITS_PER_INDEX 2

#define RCA_CARRIER_FREQ 56000 // Around 56Khz

/*
** INDEX #		    PWM ON		OFF
** 0 (LOGIC 0)	    0.50ms		1ms
** 1 (LOGIC 1)	    0.50ms		2ms
** 2 (AGC-PAUSE)	4ms		    4ms
** 3 (STOP)	        0.50ms		0ms
*/

const uint16_t RCA_Times[] PROGMEM = {
    RCA_PULSE_LEN, RCA_LOGIC_ZERO_LEN, // 0.50ms on 1ms off (logic 0)
    RCA_PULSE_LEN, RCA_LOGIC_ONE_LEN,  // 0.50ms on 2ms off (logic 1)
    RCA_AGC_LEN, RCA_LONG_PAUSE_LEN, // 4ms on 4ms off (AGC-LPAUSE)
    RCA_PULSE_LEN, 0,                  // 0.50ms on 0ms off (stop)
};

#endif