#ifndef COLOR_H
#define COLOR_H

namespace drw {


struct Color {
    Color() {
        r = 1;
        g = 1;
        b = 1;
        a = 1;
    }

    constexpr Color(float red, float green, float blue, float alpha)
        : r{red}, g{green}, b{blue}, a{alpha} {}

    constexpr Color(int red, int green, int blue)
        : r{red/255.f}, g{green/255.f}, b{blue/255.f}, a{1.f} {}

    Color(const Color& other) = default;

    float r, g, b, a;
};

} // drw

#endif // COLOR_H
