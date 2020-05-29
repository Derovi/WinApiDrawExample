#include "circleobject.h"
#include <windows.h>
#include <cmath>

void CircleObject::finish() {}

bool CircleObject::isReady() {
    return getPoints().size() == 2;
}

void CircleObject::draw(HWND& hwnd, HDC hdc) {
    if (getPoints().empty()) {
        return;
    }

    HBRUSH holdBrush;

    if (isReady() && !getColor().isTransparent()) {
        HBRUSH hBrush1 = CreateSolidBrush(getColor().getColorRef());
        holdBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush1));
    }

    if (!isReady()) {
        POINT cursor;
        GetCursorPos(&cursor);
        ScreenToClient(hwnd, &cursor);
        MoveToEx(hdc, cursor.x, cursor.y, nullptr);
        LineTo(hdc, getPoints().front().x, getPoints().front().y);
        Ellipse(hdc, cursor.x - 5, cursor.y - 5, cursor.x + 5, cursor.y + 5);
        Ellipse(hdc, getPoints().front().x - 5, getPoints().front().y - 5,
                getPoints().front().x + 5, getPoints().front().y + 5);
        int radius = std::sqrt(
                (cursor.x - getPoints().front().x) * (cursor.x - getPoints().front().x) +
                (cursor.y - getPoints().front().y) * (cursor.y - getPoints().front().y));
        Ellipse(hdc, getPoints().front().x - radius, getPoints().front().y - radius,
                getPoints().front().x + radius, getPoints().front().y + radius);
    } else {
        int radius = std::sqrt((getPoints().back().x - getPoints().front().x) *
                               (getPoints().back().x - getPoints().front().x) +
                               (getPoints().back().y - getPoints().front().y) *
                               (getPoints().back().y - getPoints().front().y));
        Ellipse(hdc, getPoints().front().x - radius, getPoints().front().y - radius,
                getPoints().front().x + radius, getPoints().front().y + radius);
    }

    if (isReady()) {
        SelectObject(hdc, holdBrush);
    }
}
