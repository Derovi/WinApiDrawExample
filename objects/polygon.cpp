#include "polygon.h"
#include <windows.h>

void PolygonObject::finish() {
    if (getPoints().size() < 3) {
        return;
    }
    finished = true;
}

bool PolygonObject::isReady() {
    return finished;
}

void PolygonObject::draw(HWND& hwnd, HDC hdc) {
    if (getPoints().empty()) {
        return;
    }

    HBRUSH holdBrush;

    if (isReady() && !getColor().isTransparent()) {
        HBRUSH hBrush1 = CreateSolidBrush(getColor().getColorRef());
        holdBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush1));
    }

    for (int index = 0; index < getPoints().size(); ++index) {
        if (!isReady()) {
            Ellipse(hdc, getPoints()[index].x - 5, getPoints()[index].y - 5,
                    getPoints()[index].x + 5, getPoints()[index].y + 5);
        }
        if (index > 0) {
            MoveToEx(hdc, getPoints()[index - 1].x, getPoints()[index - 1].y, nullptr);
            LineTo(hdc, getPoints()[index].x, getPoints()[index].y);
        }
    }
    if (!isReady()) {
        POINT cursor;
        GetCursorPos(&cursor);
        ScreenToClient(hwnd, &cursor);
        MoveToEx(hdc, getPoints().back().x, getPoints().back().y, nullptr);
        LineTo(hdc, cursor.x, cursor.y);
        Ellipse(hdc, cursor.x - 5, cursor.y - 5,
                cursor.x + 5, cursor.y + 5);
        MoveToEx(hdc, cursor.x, cursor.y, nullptr);
        LineTo(hdc, getPoints().front().x, getPoints().front().y);
    } else {
        MoveToEx(hdc, getPoints().back().x, getPoints().back().y, nullptr);
        LineTo(hdc, getPoints().front().x, getPoints().front().y);
    }
    if (isReady()) {
        SelectObject(hdc, holdBrush);
    }
}
