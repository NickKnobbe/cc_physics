#ifndef CC_UTIL
#define CC_UTIL

class CCUtil {
    public:
    static void print(const char* txt);
    static void printe(const char* txt);
    static double ccLerpProgress(double beg, double end, double amt);
    static double ccLerp(double beg, double end, double amt);
};

//CC_PRINT(txt) godot::UtilityFunctions::print(godot::Variant("CC_PHYS : "), godot::Variant(txt))

#endif