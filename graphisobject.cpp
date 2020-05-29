#include "graphisobject.h"

std::vector<POINT>& GraphicObject::getPoints() {
    return points;
}

void GraphicObject::append(POINT point) {
    points.push_back(point);
}

Color& GraphicObject::getColor() {
    return color;
}

void GraphicObject::setColor(const Color& color) {
    GraphicObject::color = color;
}
