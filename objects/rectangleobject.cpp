#include "rectangleobject.h"
#include <windows.h>


void RectangleObject::finish() {

}

bool RectangleObject::isReady() {
    return getPoints().size() == 2;
}

void RectangleObject::draw(HWND& hwnd, HDC hdc) {
    if (getPoints().empty()) {
        return;
    }

    HBRUSH holdBrush;

    if (isReady()) {
        HBRUSH hBrush1 = CreateSolidBrush(getColor().getColorRef());
        holdBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush1));
    }

    POINT first = getPoints().front();
    POINT second = getPoints().back();
    if (!isReady()) {
        GetCursorPos(&second);
        ScreenToClient(hwnd, &second);
        Ellipse(hdc, first.x - 5, first.y - 5, first.x + 5, first.y + 5);
        Ellipse(hdc, second.x - 5, second.y - 5, second.x + 5, second.y + 5);
    }

    if (first.x > second.x) {
        std::swap(first.x, second.x);
    }
    if (first.y > second.y) {
        std::swap(first.y, second.y);
    }
    Rectangle(hdc, first.x, first.y, second.x, second.y);

    if (isReady()) {
        SelectObject(hdc, holdBrush);
    }
}
