#ifndef COLOR_H
#define COLOR_H

struct Color {
    constexpr Color(float red, float green, float blue, float alpha)
        : r{red}, g{green}, b{blue}, a{alpha} {}

    constexpr Color(int red, int green, int blue)
        : r{red/255.f}, g{green/255.f}, b{blue/255.f}, a{1.f} {}

    float r, g, b, a;
};


#endif // COLOR_H
