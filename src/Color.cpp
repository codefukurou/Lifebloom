#include"Color.hpp"

rgba::rgba(void) {
    r = 0;
    g = 0;
    b = 0;
    a = 1;
}

rgba::rgba(float _r_, float _g_, float _b_, float _a_) {

    r = max(min(_r_,1.0f),0.0f);
    g = max(min(_g_,1.0f),0.0f);
    b = max(min(_b_,1.0f),0.0f);
    a = max(min(_a_,1.0f),0.0f);
}

rgba::rgba(hsva input) {
    float      hh, p, q, t, ff;
    long        i;

    a = input.a;

    if(input.s <= 0.0) {       // < is bogus, just shuts up warnings
        r = input.v;
        g = input.v;
        b = input.v;
        return;
    }
    hh = input.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = input.v * (1.0 - input.s);
    q = input.v * (1.0 - (input.s * ff));
    t = input.v * (1.0 - (input.s * (1.0 - ff)));

    switch(i) {
    case 0:
        r = input.v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = input.v;
        b = p;
        break;
    case 2:
        r = p;
        g = input.v;
        b = t;
        break;

    case 3:
        r = p;
        g = q;
        b = input.v;
        break;
    case 4:
        r = t;
        g = p;
        b = input.v;
        break;
    case 5:
    default:
        r = input.v;
        g = p;
        b = q;
        break;
    }
}

hsva::hsva(void) {
    h = 0;
    s = 0;
    v = 0;
    a = 1;
}

hsva::hsva(float _h_, float _s_, float _v_, float _a_) {
    h = fmod(_h_,360);
    s = max(min(_s_,1.0f),0.0f);
    v = max(min(_v_,1.0f),0.0f);
    a = max(min(_a_,1.0f),0.0f);
}

hsva::hsva(rgba input) {
    float      min, max, delta;

    a = input.a;

    min = input.r < input.g ? input.r : input.g;
    min = min  < input.b ? min  : input.b;

    max = input.r > input.g ? input.r : input.g;
    max = max  > input.b ? max  : input.b;

    v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        s = 0;
        h = 0; // undefined, maybe nan?
        return;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        s = 0.0;
        h = NAN;                            // its now undefined
        return;
    }
    if( input.r >= max )                           // > is bogus, just keeps compilor happy
        h = ( input.g - input.b ) / delta;        // between yellow & magenta
    else
    if( input.g >= max )
        h = 2.0 + ( input.b - input.r ) / delta;  // between cyan & yellow
    else
        h = 4.0 + ( input.r - input.g ) / delta;  // between magenta & cyan

    h *= 60.0;                              // degrees

    if( h < 0.0 )
        h += 360.0;

}
