#include "pieobject.h"
#include <windows.h>
#include <cmath>

void PieObject::finish() {}

bool PieObject::isReady() {
    return getPoints().size() == 3;
}

void PieObject::draw(HWND& hwnd, HDC hdc) {
    if (getPoints().empty()) {
        return;
    }
    POINT cursor;
    GetCursorPos(&cursor);
    ScreenToClient(hwnd, &cursor);
    if (!isReady()) {
        for (auto point : getPoints()) {
            Ellipse(hdc, point.x - 5, point.y - 5, point.x + 5, point.y + 5);
        }
    }
    Ellipse(hdc, cursor.x - 5, cursor.y - 5, cursor.x + 5, cursor.y + 5);
    if (getPoints().size() == 1) {
        MoveToEx(hdc, getPoints().front().x, getPoints().front().y, nullptr);
        LineTo(hdc, cursor.x, cursor.y);
    } else if (getPoints().size() == 2) {
        MoveToEx(hdc, getPoints().front().x, getPoints().front().y, nullptr);
        LineTo(hdc, getPoints()[1].x, getPoints()[1].y);
        MoveToEx(hdc, getPoints().front().x, getPoints().front().y, nullptr);
        LineTo(hdc, cursor.x, cursor.y);
        int radius = std::sqrt((getPoints().back().x - getPoints().front().x) *
                               (getPoints().back().x - getPoints().front().x) +
                               (getPoints().back().y - getPoints().front().y) *
                               (getPoints().back().y - getPoints().front().y));

        AngleArc(hdc, getPoints().front().x, getPoints().front().y, radius,
                 getAngle({getPoints()[1].x - getPoints().front().x,
                           getPoints()[1].y - getPoints().front().y}, {1, 0}),
                 -getAngle({getPoints()[1].x - getPoints().front().x,
                           getPoints()[1].y - getPoints().front().y},
                          {cursor.x - getPoints().front().x,
                           cursor.y - getPoints().front().y}));
    } else if (getPoints().size() == 3) {
        int radius = std::sqrt((getPoints().back().x - getPoints().front().x) *
                               (getPoints().back().x - getPoints().front().x) +
                               (getPoints().back().y - getPoints().front().y) *
                               (getPoints().back().y - getPoints().front().y));


        MoveToEx(hdc, getPoints().front().x, getPoints().front().y, nullptr);

        AngleArc(hdc, getPoints().front().x, getPoints().front().y, radius,
                 getAngle({getPoints()[1].x - getPoints().front().x,
                           getPoints()[1].y - getPoints().front().y}, {1, 0}),
                 -getAngle({getPoints()[1].x - getPoints().front().x,
                            getPoints()[1].y - getPoints().front().y},
                           {getPoints().back().x - getPoints().front().x,
                            getPoints().back().y - getPoints().front().y}));

        LineTo(hdc, getPoints().front().x, getPoints().front().y);
    }
}

double PieObject::getAngle(POINT first, POINT second) {
    return (atan2(second.y, second.x) - atan2(first.y, first.x)) * 180.0 / 3.141592653589793238463;
}
