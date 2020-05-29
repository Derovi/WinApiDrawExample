#ifndef COLOR_H
#define COLOR_H


#include <windef.h>
#include <windows.h>

class Color {
  public:
    Color();

    Color(int r, int g, int b);

    COLORREF getColorRef() const;

    int getR() const;

    void setR(int r);

    int getG() const;

    void setG(int g);

    int getB() const;

    void setB(int b);

    void change();

    bool isTransparent() const;

    void setTransparent(bool transparent);

  private:
    int r;
    int g;
    int b;

    bool transparent = false;
};


#endif //COLOR_H
