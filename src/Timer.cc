//
// Better well stolen from Sten than badly written by me - Davey
//

#include "Timer.hh"
#include <wiringPi.h>
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
    std::cout << "[Timer] Starting timer for " << milliseconds << " ms.\n";
    targetTime = millis() + milliseconds;
}

/**
 * Cancel the timer.
 */
void Timer::timer_cancel() {
    std::cout << "[Timer] Canceling timer.\n";
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
bool Timer::check_timer() {
    std::cout << "[Timer] Checking timer...\n";
    if (!is_running()) return false;

    if (millis() >= targetTime) {
        targetTime = 0;
        timer.out.timeout();
        return true;
    }
    return false;
}
