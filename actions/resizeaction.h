#ifndef RESIZEACTION_H
#define RESIZEACTION_H


#include "../action.h"

class ResizeAction : public Action {
  public:
    explicit ResizeAction(GraphicObject* object);

    void tick(int timeDelta, HWND& hwnd, HDC hdc) override;

  private:
    std::vector<std::pair<double, double> > velocities;

    static std::pair<double, double> getRandomDirection();
};

#endif  // RESIZEACTION_H
