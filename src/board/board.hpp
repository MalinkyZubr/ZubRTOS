#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "atomic.hpp"


#define OVF_FLAG_VALUE 1


// assuming 16 mhz clock
enum PrescalerDivisor {
    PRESCALE_NONE = 0b00000001,
    PRESCALE_8 = 0b00000010,
    PRESCALE_64 = 0b00000011,
    PRESCALE_256 = 0b00000100,
    PRESCALE_1024 = 0b00000101
};


class Board { // automatically use the 16 bit timer
    protected:
        virtual int set_prescaler(PrescalerDivisor prescaler_type) {};
        virtual int set_timers(uint16_t reset_value) {};
        virtual int set_interrupts() {};
    public:
        Board(PrescalerDivisor prescaler_type, uint16_t reset_value);
};


class BOARD_Atmega328p : private Board {
    protected:
        int set_prescaler(PrescalerDivisor prescaler_type);
        int set_timers(uint16_t reset_value);
        int set_interrupts();
};


class BOARD_Atmega2560 : private Board {
    protected:
        int set_prescaler(PrescalerDivisor prescaler_type);
        int set_timers(uint16_t reset_value);
        int set_interrupts();
};


#define SET_TIMER1_COMP_ISR(isr_function) { ISR(TIMER1_COMPA_vect) { isr_function(); }}

// dumb stupid little macro because im addicted to OOP :(
// will refactor later!

// #define CONFIGURE_BOARD(isr_function) \
//     do { \
//         #if defined __AVR_ATmega328__ \
//             BOARD_Atmega328p(PRESCALE_1024, 16384);
//         #elif defined __AVR_ATmega2560__ \
//             // implement later
//         #endif \
//         SET_TIMER1_COMP_ISR(isr_function) \
//     } while(0)


#endif