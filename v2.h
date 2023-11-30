#ifndef CC_V2
#define CC_V2

class V2 {
    public:
    float x = 0.0;
    float y = 0.0;

    V2();
    V2(float _x, float _y);
    V2(const V2& other); // Copy constructor
    ~V2();

    float dist(V2& to);
    float dist_sqd(V2& to);

    V2 operator+(V2 other);
};

#endif