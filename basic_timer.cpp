#include <basic_timer.h>

BasicTimer::BasicTimer() : time_per_action(1.0) {}
BasicTimer::BasicTimer(double _time_per) : time_per_action(_time_per) {}

void BasicTimer::begin() {

}

int BasicTimer::process(double delta) {
    time_since_last_action += delta;
    int actions = 0;
    while (time_since_last_action >= time_per_action) {
        time_since_last_action -= time_per_action;
        ++actions;
    }
    return actions;
}