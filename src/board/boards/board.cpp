#include "board.hpp"


Board::Board(PrescalerDivisor prescaler_type, uint16_t reset_value) {
    ATOMIC_OPERATION([this, prescaler_type, reset_value]() -> void {
        this->set_prescaler(prescaler_type);
        this->set_timers(reset_value);
        this->set_interrupts();
    });
}