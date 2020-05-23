#include <windows.h>
#include <windowsx.h>

#include <cmath>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

#include "graphisobject.h"
#include "objectmanager.h"
#include "objects/segmentobject.h"

LRESULT MessagesHandler(
        HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param);

HINSTANCE instance_handle;

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
            /* dwStyle =      */ WS_OVERLAPPEDWINDOW,
            /* X =            */ CW_USEDEFAULT,
            /* Y =            */ CW_USEDEFAULT,
            /* nWidth =       */ 500,
            /* nHeight =      */ 500,
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
        manager.registerObject("Segment", [] {
            return static_cast<GraphicObject*>(new SegmentObject());
        });
    }

    ~MultipleLinesPainter() {
        for (auto object : objects) {
            delete object;
        }
    }

    LRESULT Handle(
            HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) {
        switch (message_code) {
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
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(window_handle, &ps);
                for (auto object : objects) {
                    object->draw(window_handle, hdc);
                }
                EndPaint(window_handle, &ps);
                break;
            }
            case WM_SIZE: {
                InvalidateRect(window_handle, nullptr, true);
                break;
            }
            case WM_MOUSEMOVE: {
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
};

LRESULT MessagesHandler(
        HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) {
    static MultipleLinesPainter multiple_lines_painter;
    return multiple_lines_painter.Handle(
            window_handle, message_code, w_param, l_param);
}