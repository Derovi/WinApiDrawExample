#ifndef SEGMENTOBJECT_H
#define SEGMENTOBJECT_H

#include "../graphisobject.h"

class SegmentObject : public GraphicObject {
  public:
    void finish() override;

    bool isReady() override;

    void draw(HWND& hwnd, HDC hdc) override;

  private:
};


#endif //SEGMENTOBJECT_H
