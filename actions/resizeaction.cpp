#include <random>
#include <chrono>
#include <iostream>
#include "resizeaction.h"

ResizeAction::ResizeAction(GraphicObject* object): Action(object) {}

void ResizeAction::tick(int delta, HWND& hwnd, HDC hdc) {
    if (!getObject()->isReady()) {
        return;
    }

    if (velocities.empty()) {
        velocities.resize(getObject()->getPoints().size());
        for (int index = 0;
             index < getObject()->getPoints().size();
             ++index) {
            velocities[index] = getRandomDirection();
        }
    }

    RECT rect;
    GetWindowRect(hwnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    for (int index = 0;
         index < getObject()->getPoints().size();
         ++index) {
        getObject()->getPoints()[index].x += velocities[index].first * delta;
        getObject()->getPoints()[index].y += velocities[index].second * delta;
        if (getObject()->getPoints()[index].x <= 0 || getObject()->getPoints()[index].y <= 0 ||
            getObject()->getPoints()[index].x >= width ||
            getObject()->getPoints()[index].y >= height) {
            velocities[index] = getRandomDirection();
        }
    }
}

std::pair<double, double> ResizeAction::getRandomDirection() {
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::make_pair((static_cast<double>(rnd() % 100) - 50) / 100.0,
                          (static_cast<double>(rnd() % 100) - 50) / 100.0);
}
