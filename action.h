#ifndef ACTION_H
#define ACTION_H

#include "graphisobject.h"

#include <chrono>
#include <windows.h>
#include <windowsx.h>
#include <winbase.h>

class Action {
  public:
    explicit Action(GraphicObject* object): object(object) {}

    virtual void tick(int timeDelta, HWND& hwnd, HDC hdc) = 0;

    GraphicObject* getObject() const {
        return object;
    }

    virtual ~Action() = default;;

  private:
    GraphicObject* object;
};

#endif  // ACTION_H
