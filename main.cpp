#include <windows.h>
#include <windowsx.h>
#include <winbase.h>

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "graphisobject.h"
#include "objectmanager.h"
#include "objects/segmentobject.h"
#include "objects/rectangleobject.h"
#include "objects/brokenlineobject.h"
#include "objects/polygon.h"
#include "objects/circleobject.h"
#include "objects/ellipseobject.h"
#include "objects/pieobject.h"
#include "animation.h"

#ifndef UNICODE
#define UNICODE
#endif

LRESULT MessagesHandler(
        HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param);

HINSTANCE instance_handle;

static HDC hdcBackground = nullptr;

INT WinMain(HINSTANCE instance_handle_arg, HINSTANCE,
            LPSTR /* command_line */, int n_cmd_show) {
    instance_handle = instance_handle_arg;

    // Register the window class.
    const char kClassName[] = "msg_server_class";
    WNDCLASS window_class = {};
    window_class.lpfnWndProc = MessagesHandler;
    window_class.hInstance = instance_handle;
    window_class.lpszClassName = kClassName;
    window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
    window_class.hbrBackground = GetStockBrush(WHITE_BRUSH);
    RegisterClass(&window_class);

    // Create the window.
    HWND handle_of_window = CreateWindowEx(
            /* dwExStyle =    */ 0,
            /* lpClassName =  */ kClassName,
            /* lpWindowName = */ "WinAPI Example",
            /* dwStyle =      */ WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
            /* X =            */ CW_USEDEFAULT,
            /* Y =            */ CW_USEDEFAULT,
            /* nWidth =       */ 1600,
            /* nHeight =      */ 1100,
            /* hWndParent =   */ nullptr,
            /* hMenu =        */ nullptr,
            /* hInstance =    */ instance_handle,
            /* lpParam =      */ nullptr
    );
    if (handle_of_window == nullptr) {
        return 1;
    }

    // Show the window.
    ShowWindow(handle_of_window, n_cmd_show);

    // Run the message loop.
    MSG message = {};
    while (GetMessage(&message, nullptr, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return (int) message.wParam;
}

class MultipleLinesPainter {
  public:
    MultipleLinesPainter() {
        manager.registerObject(L"Segment", [] {
            return static_cast<GraphicObject*>(new SegmentObject());
        });
        manager.registerObject(L"Rectangle", [] {
            return static_cast<GraphicObject*>(new RectangleObject());
        });
        manager.registerObject(L"Broken line", [] {
            return static_cast<GraphicObject*>(new BrokenLineObject());
        });
        manager.registerObject(L"Pentagon", [] {
            return static_cast<GraphicObject*>(new PolygonObject());
        });
        manager.registerObject(L"Circle", [] {
            return static_cast<GraphicObject*>(new CircleObject());
        });
        manager.registerObject(L"Ellipse", [] {
            return static_cast<GraphicObject*>(new EllipseObject());
        });
        manager.registerObject(L"Pie", [] {
            return static_cast<GraphicObject*>(new PieObject());
        });
        animation = new Animation(&objects);
    }

    ~MultipleLinesPainter() {
        for (auto object : objects) {
            delete object;
        }
        delete animation;
    }

    LRESULT Handle(
            HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) {
        switch (message_code) {
            case WM_CREATE: {
                SetTimer(window_handle, TIMER_ID, 20 /* millis */, NULL);
                background = (HBITMAP) LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                hdcBackground = CreateCompatibleDC(NULL);
                SelectObject(hdcBackground, background);
                break;
            }
            case WM_TIMER: {
                InvalidateRect(window_handle, nullptr, true);
                break;
            }
            case WM_LBUTTONDOWN: {
                POINT clickedPoint = {LOWORD(l_param), HIWORD(l_param)};
                if (objects.empty() || objects.back()->isReady()) {
                    std::cerr << "new!";
                    objects.push_back(manager.create());
                }
                std::cerr << "append!" << std::endl;
                objects.back()->append(clickedPoint);
                InvalidateRect(window_handle, nullptr, true);
                break;
            }
            case WM_RBUTTONDOWN: {
                if (!objects.empty()) {
                    objects.pop_back();
                }
                InvalidateRect(window_handle, nullptr, true);
                break;
            }
            case WM_KEYDOWN: {
                PAINTSTRUCT ps;

                HDC hdc = BeginPaint(window_handle, &ps);
                if (w_param == VK_LEFT) {
                    manager.prev();
                } else if (w_param == VK_RIGHT) {
                    manager.next();
                } else if (w_param == VK_UP) {
                    animation->setSpeed(animation->getSpeed() + 0.1);
                } else if (w_param == VK_DOWN) {
                    animation->setSpeed(std::max(0.0, animation->getSpeed() - 0.1));
                } else if (w_param == VK_RETURN) {
                    if (!objects.empty()) {
                        objects.back()->finish();
                    }
                } else if (w_param == 'C' && GetKeyState(VK_CONTROL) < 0) {
                    objects.clear();
                } else if (w_param == 'C') {
                    for (auto* object : objects) {
                        object->getColor().change();
                    }
                } else if (w_param == 'M') {
                    animation->changeMode();
                } else if (w_param == 'T') {
                    for (auto* object : objects) {
                        object->getColor().setTransparent(!object->getColor().isTransparent());
                    }
                } else if (w_param == 'R') {
                    animation->restart(window_handle, hdc);
                } else if (w_param == 'I') {
                    ++penWidth;
                } else if (w_param == 'D') {
                    penWidth = std::max(penWidth - 1, 1);
                } else if (w_param == VK_SPACE) {
                    if (animation->isPlaying()) {
                        animation->pause();
                    } else {
                        animation->resume();
                    }
                }
                EndPaint(window_handle, &ps);
                InvalidateRect(window_handle, nullptr, true);
                break;
            }
            case WM_ERASEBKGND: {
                return (LRESULT) 1;
            }
            case WM_PAINT: {
                PAINTSTRUCT ps;

                HDC hdc = BeginPaint(window_handle, &ps);

                RECT rcWindow;
                HDC hdcMem;
                HBITMAP hbmMem;
                HANDLE hbmOld;

                GetClientRect(window_handle, &rcWindow);
                hdcMem = CreateCompatibleDC(hdc);
                hbmMem = CreateCompatibleBitmap(hdc,
                                                rcWindow.right - rcWindow.left,
                                                rcWindow.bottom - rcWindow.top);
                hbmOld = SelectObject(hdcMem, hbmMem);
                BitBlt(hdcMem,
                       rcWindow.left, rcWindow.top,
                       rcWindow.right - rcWindow.left,
                       rcWindow.bottom - rcWindow.top,
                       hdcBackground,
                       0, 0,
                       SRCCOPY);

                SelectObject(hdcMem, GetStockObject(HOLLOW_BRUSH));

                LOGBRUSH brush;
                COLORREF col = RGB(0, 0, 0);
                DWORD pen_style = PS_SOLID | PS_JOIN_MITER | PS_GEOMETRIC;

                brush.lbStyle = BS_SOLID;
                brush.lbColor = col;
                brush.lbHatch = 0;

                HPEN hWhitePen = ExtCreatePen(pen_style, penWidth, &brush, 0, NULL);
                HPEN hOldPen = static_cast<HPEN>(SelectObject(hdcMem, hWhitePen));

                animation->tick(window_handle, hdcMem);

                for (auto object : objects) {
                    object->draw(window_handle, hdcMem);
                }

                SelectObject(hdc, hOldPen);

                // draw text

                DWORD color = GetSysColor(COLOR_BTNFACE);
                SetBkColor(hdcMem, color);

                HFONT hFont = CreateFontW(15, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0,
                                          0, 0, 1, 0, L"Georgia");
                auto holdFont = static_cast<HFONT>(SelectObject(hdc, hFont));

                // draw status
                RECT rect;
                GetWindowRect(window_handle, &rect);

                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;

                std::wstring text = L"Selected object: " + manager.getName();
                TextOutW(hdcMem, width / 2 - 3 * lstrlenW(text.c_str()), 50, text.c_str(),
                         lstrlenW(text.c_str()));

                // draw help

                text = L"Use left and right arrows to change drawing object";
                TextOutW(hdcMem, 100, height - 280, text.c_str(),
                         lstrlenW(text.c_str()));

                text = L"Use left mouse button to add a point to the drawing object";
                TextOutW(hdcMem, 100, height - 240, text.c_str(),
                         lstrlenW(text.c_str()));

                text = L"Use right mouse button to undo object drawing";
                TextOutW(hdcMem, 100, height - 200, text.c_str(),
                         lstrlenW(text.c_str()));

                text = L"Use ENTER to finish object drawing";
                TextOutW(hdcMem, 100, height - 160, text.c_str(),
                         lstrlenW(text.c_str()));

                text = L"Use ctrl + C to clear all objects from the screen";
                TextOutW(hdcMem, 100, height - 120, text.c_str(),
                         lstrlenW(text.c_str()));

                text = L"Use SPACE to start/ stop animation";
                TextOutW(hdcMem, 100, height - 80, text.c_str(),
                         lstrlenW(text.c_str()));

                text = L"Use R to restart animation";
                TextOutW(hdcMem, 100, height - 40, text.c_str(),
                         lstrlenW(text.c_str()));

                DeleteObject(hFont);

                BitBlt(hdc,
                       rcWindow.left, rcWindow.top,
                       rcWindow.right - rcWindow.left,
                       rcWindow.bottom - rcWindow.top,
                       hdcMem,
                       0, 0,
                       SRCCOPY);

                SelectObject(hdcMem, hbmOld);
                DeleteObject(hbmMem);
                DeleteDC(hdcMem);

                EndPaint(window_handle, &ps);
                break;
            }
            case WM_SIZE: {
                InvalidateRect(window_handle, nullptr, true);
                break;
            }
            case WM_DESTROY: {
                PostQuitMessage(0);
                break;
            }
            default: {
                return DefWindowProc(window_handle, message_code, w_param, l_param);
            }
        }
        return 0;
    }

  private:
    std::vector<GraphicObject*> objects;
    ObjectManager manager;
    Animation* animation;
    HBITMAP background = NULL;

    int penWidth = 4;
    int TIMER_ID;
};

LRESULT MessagesHandler(
        HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) {
    static MultipleLinesPainter multiple_lines_painter;
    return multiple_lines_painter.Handle(
            window_handle, message_code, w_param, l_param);
}