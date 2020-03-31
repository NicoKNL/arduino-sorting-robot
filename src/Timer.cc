//
// Better well stolen from Sten than badly written by me - Davey
//

#include "Timer.hh"

/**
 * Implementation of the timer.
 *
 * Note: the behavior of the timer is not self-contained.
 * The timeout check must be done on the main event loop, to circumvent the creation of threads and for simplicity.
 */
Timer::Timer(const dzn::locator &loc) : skel::Timer(loc) {
    targetTime = 0;
}

/**
 * Starts the timer by setting the target value to the current time plus the provided offset.
 */
void Timer::timer_start(long milliseconds) {
    targetTime = millis() + milliseconds;
}

/**
 * Cancel the timer.
 */
void Timer::timer_cancel() {
    targetTime = 0;
}

/**
 * Checks whether the timer currently is running or not.
 */
bool Timer::is_running() {
    return targetTime != 0;
}

/**
 * Checks whether the timer has run out.
 */
void Timer::check_timer() {
    if (!is_running()) return;

    if (millis() >= targetTime) {
        targetTime = 0;
        timer.out.timeout();
    }
}