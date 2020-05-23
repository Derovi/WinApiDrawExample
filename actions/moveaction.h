#ifndef MOVEACTION_H
#define MOVEACTION_H


#include "../action.h"

class MoveAction : public Action {
  public:
    explicit MoveAction(GraphicObject* object);

    void tick(int timeDelta, HWND& hwnd, HDC hdc) override;

  private:
    double dx;
    double dy;
};

#endif  // MOVEACTION_H
