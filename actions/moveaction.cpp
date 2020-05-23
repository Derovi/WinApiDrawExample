#include <random>
#include <chrono>
#include "moveaction.h"

MoveAction::MoveAction(GraphicObject* object): Action(object) {
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    dx = (rnd() % 100) / 100.0 - 0.5;
    dy = (rnd() % 100) / 100.0 - 0.5;
}

void MoveAction::tick(int delta, HWND& hwnd, HDC hdc) {
    if (!getObject()->isReady()) {
        return;
    }
    RECT rect;
    GetWindowRect(hwnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    bool changeDir = false;

    for (POINT& point : getObject()->getPoints()) {
        point.x += dx * delta;
        point.y += dy * delta;
        if (point.x <= 0 || point.y <= 0 || point.x >= width || point.y >= height) {
            changeDir = true;
        }
    }

    if (changeDir) {
        std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
        dx = (rnd() % 100) / 100.0 - 0.5;
        dy = (rnd() % 100) / 100.0 - 0.5;
    }
}
