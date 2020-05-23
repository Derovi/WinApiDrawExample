#ifndef GRAPHISOBJECT_H
#define GRAPHISOBJECT_H

#include <vector>
#include <windef.h>

class GraphicObject {
  public:
    void append(POINT point);

    virtual void finish() = 0;

    virtual bool isReady() = 0;

    virtual void draw(HWND& hwnd, HDC hdc) = 0;

    std::vector<POINT>& getPoints();

    virtual ~GraphicObject() = default;
  private:
    std::vector<POINT> points;
};


#endif  // GRAPHISOBJECT_H
