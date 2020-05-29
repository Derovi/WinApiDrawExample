#include "animation.h"
#include "actions/moveaction.h"
#include "actions/resizeaction.h"

#include <windows.h>
#include <windowsx.h>
#include <winbase.h>
#include <iostream>

Animation::Animation(std::vector<GraphicObject*>* objects):
        objects(objects), time(0), lastTickTime(GetCurrentTime()),
        rnd(std::chrono::steady_clock::now().time_since_epoch().count()) {}

bool Animation::isFinished() {
    return finished;
}

bool Animation::isPlaying() {
    return !paused;
}

void Animation::pause() {
    paused = true;
}

void Animation::resume() {
    paused = false;
}

void Animation::restart(HWND& hwnd, HDC hdc) {
    finished = false;
    time = 0;
    int delta = 1200;
    int subDelta = 5;
    for (int index = 0; index < delta * speed / subDelta; ++index) {
        perform(subDelta, hwnd, hdc);
    }
}

void Animation::tick(HWND& hwnd, HDC hdc) {
    while (actions.size() > objects->size()) {
        actions.pop_back();
    }
    int sz = actions.size();
    for (int index = sz; index < objects->size(); ++index) {
        //actions.push_back(new MoveAction((*objects)[index]));
        actions.push_back(new ResizeAction((*objects)[index]));
    }
    int64_t currentTime = GetCurrentTime();
    int64_t delta = currentTime - lastTickTime;
    lastTickTime = currentTime;
    if (paused) {
        return;
    }
    time += delta;
    int subDelta = 5;
    for (int index = 0; index < delta * speed / subDelta; ++index) {
        perform(subDelta, hwnd, hdc);
    }
}

void Animation::perform(int delta, HWND& hwnd, HDC hdc) {
    for (auto action : actions) {
        action->tick(delta, hwnd, hdc);
    }
}

double Animation::getSpeed() const {
    return speed;
}

void Animation::setSpeed(double speed) {
    Animation::speed = speed;
}

Animation::~Animation() {
    for (auto action : actions) {
        delete action;
    }
}
