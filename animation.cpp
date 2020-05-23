#include "animation.h"

#include <windows.h>
#include <windowsx.h>
#include <winbase.h>
#include <iostream>

Animation::Animation(std::vector<GraphicObject*>* objects):
        objects(objects), time(0), lastTickTime(GetCurrentTime()) {}

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

void Animation::restart() {
    finished = false;
    time = 0;
}

void Animation::tick() {
    int64_t currentTime = GetCurrentTime();
    int64_t delta = currentTime - lastTickTime;
    lastTickTime = currentTime;
    if (paused) {
        return;
    }
    time += delta;
}
