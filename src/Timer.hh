//
// Better well stolen from Sten than badly written by me - Davey
//

#ifndef TIMER_HH
#define TIMER_HH

#include "ITimer.hh"

/**
 * This is manually written code for the native component.
 *
 * @author Sten Wessel
 */
class Timer : public skel::Timer {
    void timer_start(long milliseconds);
    void timer_cancel();
    bool is_running();

    uint targetTime;

public:
    Timer(const dzn::locator& loc);
    bool check_timer();
};

#endif //TIMER_HH
