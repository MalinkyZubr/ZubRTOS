#include "board.cpp"


int BOARD_Atmega328p::set_prescaler(PrescalerDivisor prescaler_type) {
    TCCR1B |= prescaler_type; // set the prescaler value register
    return 1;
}


int BOARD_Atmega328p::set_timers(uint16_t reset_value) {
    TCCR1A = 0;
    OCR1A |= reset_value; // 16 bit value for the comparison timer value, using timer A
    TCCR1B |= (1 << WGM12); // set to use the 16 bit comparison value for resets in OCR1AH
    return 1;
}


int BOARD_Atmega328p::set_interrupts() {
    TIMSK1 |= (1 << OCIE1A); // enabling interrupts on timer 1 A
    return 1;
}