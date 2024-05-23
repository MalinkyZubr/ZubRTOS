must be careful! doa study to ensure this is all threadsafe with the mutual dereferencing. What if they are interrupted in the middle of dereferencing? might still end up with dangling pointers

implement reference counting!

NEED ATOMIC OPERATIONS!
Some operations need the power to temporarily disable interrupts! Each interrupt has its own interrupt bit so this is fine. memory management must be atomic!

all setup code (eg, similar to bootloader) must take place without interrupts!

for interrupts in task scheduler, the interrupt will only trigger the re-evaluation stage of the MCU

SREG global interrupt flag is set to 0 when interrupt occurs, disables all interrupts. Must set to 1 to enable pre-emption

figure out how the stack works!