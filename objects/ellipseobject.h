#ifndef ELLIPSEOBJECT_H
#define ELLIPSEOBJECT_H

#include "../graphisobject.h"

class EllipseObject : public GraphicObject {
  public:
    void finish() override;

    bool isReady() override;

    void draw(HWND& hwnd, HDC hdc) override;

  private:
};


#endif //ELLIPSEOBJECT_H
