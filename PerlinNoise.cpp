#include "PerlinNoise.h"
float interpolate(float a0, float a1, float w) {
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

vector2 randomVector(int ix, int iy) {
    // im ngl i just straight up coppied this hashing function from the wiki
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w - s;
    b *= 1911520717; a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    vector2 v;
    v.x = cos(random); v.y = sin(random); //polar cords 
    return v;
}

float dotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    vector2 gradient = randomVector(ix, iy);

    // Compute the distance vector or the vector direction
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    // dot product between that corner and 
    return (dx * gradient.x + dy * gradient.y);
}

float perlin(float x, float y) {
    // detemin the cell 

    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    //determin weights here
    // how close is the point to the corners 
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0, n1, ix0, ix1, value;

    //finf the vector between the corner and the point given
    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    // then takes theta and
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return value;

}