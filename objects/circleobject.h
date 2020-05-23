#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "../graphisobject.h"

class CircleObject : public GraphicObject {
  public:
    void finish() override;

    bool isReady() override;

    void draw(HWND& hwnd, HDC hdc) override;

  private:
};

#endif  //CIRCLEOBJECT_H
