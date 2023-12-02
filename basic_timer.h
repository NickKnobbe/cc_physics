#ifndef CC_BASIC_TIMER
#define CC_BASIC_TIMER

class BasicTimer {
private:

public:
    double time_since_last_action;
    double time_per_action;
    BasicTimer();
    BasicTimer(double time_per);
    void begin();
    int process(double delta);
};

#endif