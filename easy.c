#include <X11/Xlib.h>
#include <unistd.h>

#include "./easy.h"

Display *disp = 0;
Window  win;
GC      gc;

uint16_t size;
_Bool quit;
uint8_t prevR, prevG, prevB;

void run(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint16_t pixelSize,
    void (*updateFunction)(),
    uint16_t updateSpeed,
    _Bool clearBetweenUpdates
) {
    size = pixelSize;
    quit = false;

    disp = XOpenDisplay(0);

    win = XCreateSimpleWindow(
              disp,
              DefaultRootWindow(disp),
              0,
              0,
              width * pixelSize,
              height * pixelSize,
              0,
              BlackPixel(disp, DefaultScreen(disp)),
              BlackPixel(disp, DefaultScreen(disp))
          );

    XSetWindowAttributes attr;
    attr.backing_store = Always;
    XChangeWindowAttributes(
        disp,
        win,
        CWBackingStore,
        &attr
    );

    XSelectInput(
        disp,
        win,
        KeyPressMask | ButtonPressMask | StructureNotifyMask
    );

    XMapWindow(disp, win);

    XWindowChanges changes;
    changes.x = x;
    changes.y = y; 
    XConfigureWindow(
        disp,
        win,
        CWX | CWY,
        &changes
    );

    gc = XCreateGC(disp, win, 0, 0);

    XEvent event;
    do {
        XNextEvent(disp, &event);
    } while (event.type != MapNotify);

    prevR = prevG = prevB = 0;

    do {
        XCheckMaskEvent(disp, -1, &event);
        quit = event.type == KeyPress || event.type == ButtonPress;

        if(clearBetweenUpdates) {
            XClearWindow(disp, win);
        }
        (*updateFunction)();
        XFlush(disp);

        usleep(!quit ? 1000 * updateSpeed : 0);
    } while (!quit);
}

void set(
    uint16_t x,
    uint16_t y,
    uint8_t r,
    uint8_t g,
    uint8_t b
) {
    if (r != prevR || g != prevG || b != prevB) {
        XColor c;
        c.pixel = r << 16 | g << 8 | b;
        XSetForeground(disp, gc, c.pixel);

        prevR = r;
        prevG = g;
        prevB = b;
    }

    XFillRectangle(disp, win, gc, x * size, y * size, size, size);
}
