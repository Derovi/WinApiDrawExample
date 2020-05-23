#ifndef BROKENLINEOBJECT_H
#define BROKENLINEOBJECT_H


#include "../graphisobject.h"

class BrokenLineObject : public GraphicObject {
  public:
    void finish() override;

    bool isReady() override;

    void draw(HWND& hwnd, HDC hdc) override;

  private:
    bool finished = false;
};


#endif //BROKENLINEOBJECT_H
