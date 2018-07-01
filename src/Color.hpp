#include<cmath>
#include<algorithm>

using namespace std;

struct rgba;
struct hsva;

struct rgba{
    float r, g, b, a;

    rgba(void);
    rgba(float _r_, float _g_, float _b_, float _a_);
    rgba(hsva input);
};

struct hsva{
    float h, s, v, a;

    hsva(void);
    hsva(float _h_, float _s_, float _v_, float _a_);
    hsva(rgba input);
};