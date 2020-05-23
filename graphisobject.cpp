#include "graphisobject.h"

std::vector<POINT>& GraphicObject::getPoints() {
    return points;
}

void GraphicObject::append(POINT point) {
    points.push_back(point);
}
