#include "segmentobject.h"
#include <windows.h>

void SegmentObject::finish() {}

bool SegmentObject::isReady() {
    return getPoints().size() == 2;
}

void SegmentObject::draw(HWND& hwnd, HDC hdc) {
    if (getPoints().empty()) {
        return;
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
    } else {
        MoveToEx(hdc, getPoints().front().x, getPoints().front().y, nullptr);
        LineTo(hdc, getPoints().back().x, getPoints().back().y);
    }
}
