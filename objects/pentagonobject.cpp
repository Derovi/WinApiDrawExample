#include "pentagonobject.h"
#include <windows.h>

void PentagonObject::finish() {
    if (getPoints().size() < 3) {
        return;
    }
    finished = true;
}

bool PentagonObject::isReady() {
    return finished;
}

void PentagonObject::draw(HWND& hwnd, HDC hdc) {
    if (getPoints().empty()) {
        return;
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

}