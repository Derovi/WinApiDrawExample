#ifndef A\NIMATION_H
#define ANIMATION_H

#include <cstdint>
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>

#include "graphisobject.h"
#include "action.h"

class Animation {
  public:
    explicit Animation(std::vector<GraphicObject*>* objects);

    void tick(HWND& hwnd, HDC hdc);

    bool isFinished();

    bool isPlaying();

    void pause();

    void resume();

    void changeMode();

    void restart(HWND& hwnd, HDC hdc);

    double getSpeed() const;

    void setSpeed(double speed);

    ~Animation();

  private:
    std::vector<GraphicObject*>* objects;
    std::vector<Action*> actions;

    void perform(int delta, HWND& hwnd, HDC hdc);

    void loadObject(GraphicObject* object);

    bool paused = true;
    bool finished = false;

    int64_t time;
    int64_t lastTickTime;

    std::mt19937 rnd;

    double speed = 1;
    int mode = 0;
};


#endif //ANIMATION_H
