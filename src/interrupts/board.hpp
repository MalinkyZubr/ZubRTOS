#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
//#include <Arduino.h>
#include "atomic.h"


#define OVF_FLAG_VALUE 1


class Board {
    protected:
        virtual int set_prescaler();
        virtual int set_timers();
        virtual int set_interrupts();
    public:
        Board();
};


// assuming 16 mhz clock
enum PrescalerDivisor {
    PRESCALE_NONE = 1,
    PRESCALE_8 = 2,
    PRESCALE_64 = 3,
    PRESCALE_256 = 4,
    PRESCALE_1024 = 5
};


#if defined(AVR_ATmega328)
    #define CLOCK_SPEED_MHZ 16
    enum Timers {
        TIMER_0 = 8,
        TIMER_1 = 16,
        TIMER_2 = 8
    }

    void set_prescaler(TickLengths tick_length);
    void timer_setup(uint8_t tick_period);

#elif defined(AVR_ATmega2560)
    #define CLOCK_SPEED_MHZ 16
    enum Timers {
        TIMER_0 = 8,
        TIMER_1 = 16,
        TIMER_2 = 8,
        TIMER_3 = 16,
        TIMER_4 = 16,
        TIMER_5 = 16
    }
#else
    #warning "Board type not compatible! Atmega 2560 & 328p supported"
    enum Timers {};
#endif

#endif