#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "../graphisobject.h"

class RectangleObject : public GraphicObject {
  public:
    void finish() override;

    bool isReady() override;

    void draw(HWND& hwnd, HDC hdc) override;

  private:
};


#endif //RECTANGLEOBJECT_H
