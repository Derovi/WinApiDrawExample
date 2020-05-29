#ifndef POLYGON_H
#define POLYGON_H

#include "../graphisobject.h"

class PolygonObject : public GraphicObject {
  public:
    void finish() override;

    bool isReady() override;

    void draw(HWND& hwnd, HDC hdc) override;

  private:
    bool finished = false;
};


#endif //POLYGON_H
