#include "board.hpp"


Board::Board() {
    ATOMIC_OPERATION([this]() -> void {
        this->set_prescaler();
        this->set_timers();
        this->set_interrupts();
    });
}