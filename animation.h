#ifndef ANIMATION_H
#define ANIMATION_H

#include <cstdint>
#include "graphisobject.h"

class Animation {
  public:
    explicit Animation(std::vector<GraphicObject*>* objects);

    void tick();

    bool isFinished();

    bool isPlaying();

    void pause();

    void resume();

    void restart();

  private:
    std::vector<GraphicObject*>* objects;

    bool paused = true;
    bool finished = false;

    int64_t time;
    int64_t lastTickTime;
};


#endif //ANIMATION_H
