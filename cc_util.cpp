#include "cc_util.h"
#include <godot_cpp/variant/utility_functions.hpp>

void CCUtil::print(const char* txt) {
    godot::UtilityFunctions::print(godot::Variant("CC_PHYS: "), godot::Variant(txt));
}

void CCUtil::printe(const char* txt) {
    godot::UtilityFunctions::print(godot::Variant("CC_PHYS (ERROR): "), godot::Variant(txt));
}

double CCUtil::ccLerpProgress(double beg, double end, double amt) {
    double prog = amt - beg;
    if (prog <= 0.0) return 0.0;
    return (end - beg) / prog;
}