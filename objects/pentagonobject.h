#ifndef PENTAGONOBJECT_H
#define PENTAGONOBJECT_H

#include "../graphisobject.h"

class PentagonObject : public GraphicObject {
  public:
    void finish() override;

    bool isReady() override;

    void draw(HWND& hwnd, HDC hdc) override;

  private:
    bool finished = false;
};


#endif //PENTAGONOBJECT_H
