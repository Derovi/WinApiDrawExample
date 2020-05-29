#include "color.h"

int Color::getR() const {
    return r;
}

void Color::setR(int r) {
    Color::r = r;
}

int Color::getG() const {
    return g;
}

void Color::setG(int g) {
    Color::g = g;
}

int Color::getB() const {
    return b;
}

void Color::setB(int b) {
    Color::b = b;
}

Color::Color(int r, int g, int b): r(r), g(g), b(b) {}

Color::Color() : r(rand() % 255), g(rand() % 255), b(rand() % 255) {}

COLORREF Color::getColorRef() const {
    return RGB(r, g, b);
}

void Color::change() {
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
}

bool Color::isTransparent() const {
    return transparent;
}

void Color::setTransparent(bool transparent) {
    Color::transparent = transparent;
}
