#include "ellipseobject.h"
#include <windows.h>
#include <cmath>

void EllipseObject::finish() {}

bool EllipseObject::isReady() {
    return getPoints().size() == 3;
}

void EllipseObject::draw(HWND& hwnd, HDC hdc) {
    if (getPoints().empty()) {
        return;
    }

    HBRUSH holdBrush;

    if (isReady() && !getColor().isTransparent()) {
        HBRUSH hBrush1 = CreateSolidBrush(getColor().getColorRef());
        holdBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush1));
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
        LineTo(hdc, getPoints().front().x, cursor.y);
    } else if (getPoints().size() == 2) {
        MoveToEx(hdc, getPoints().front().x, getPoints().front().y, nullptr);
        LineTo(hdc, getPoints().front().x, getPoints()[1].y);
        MoveToEx(hdc, getPoints().front().x, getPoints().front().y, nullptr);
        LineTo(hdc, cursor.x, getPoints().front().y);
        int xDelta = std::abs(getPoints()[0].x - cursor.x);
        int yDelta = std::abs(getPoints()[1].y - getPoints().front().y);
        Ellipse(hdc, getPoints().front().x - xDelta, getPoints().front().y - yDelta,
                getPoints().front().x + xDelta, getPoints().front().y + yDelta);
    } else if (getPoints().size() == 3) {
        int xDelta = std::abs(getPoints()[0].x - getPoints().back().x);
        int yDelta = std::abs(getPoints()[1].y - getPoints().front().y);
        Ellipse(hdc, getPoints().front().x - xDelta, getPoints().front().y - yDelta,
                getPoints().front().x + xDelta, getPoints().front().y + yDelta);
    }

    if (isReady()) {
        SelectObject(hdc, holdBrush);
    }
}
