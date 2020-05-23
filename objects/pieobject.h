#ifndef PIEOBJECT_H
#define PIEOBJECT_H

#include "../graphisobject.h"

class PieObject : public GraphicObject {
  public:
    void finish() override;

    bool isReady() override;

    void draw(HWND& hwnd, HDC hdc) override;

  private:
    double getAngle(POINT first, POINT second);
};


#endif //PIEOBJECT_H
