//
// Created by s28 on 3/6/2026.
//

#include "OS/Grapich/windows.h"
#include "OS/Grapich/gui.h"
#include <stdlib.h>
#include <string.h>

/* Internal window structure */
typedef struct _WINDOW_OBJECT {
    int x;
    int y;
    int width;
    int height;
    DWORD style;
    DWORD ex_style;
    char title[128];
    struct _WINDOW_OBJECT* parent;
} WINDOW_OBJECT;


/* OS API implementation */
HWND WINAPI CreateWindowEx(
        DWORD dwExStyle,
LPCSTR lpClassName,
        LPCSTR lpWindowName,
DWORD dwStyle,
int X,
int Y,
int nWidth,
int nHeight,
        HWND hWndParent,
HMENU hMenu,
        HINSTANCE hInstance,
LPVOID lpParam
) {
(void)lpClassName;
(void)hMenu;
(void)hInstance;
(void)lpParam;

/* Allocate window object */
WINDOW_OBJECT* win = (WINDOW_OBJECT*)malloc(sizeof(WINDOW_OBJECT));
if (!win) {
return NULL;
}

/* Initialize structure */
win->x = X;
win->y = Y;
win->width = nWidth;
win->height = nHeight;
win->style = dwStyle;
win->ex_style = dwExStyle;
win->parent = (WINDOW_OBJECT*)hWndParent;

if (lpWindowName) {
strncpy(win->title, lpWindowName, sizeof(win->title) - 1);
win->title[sizeof(win->title) - 1] = '\0';
} else {
win->title[0] = '\0';
}

/* Register window with GUI manager */
gui_register_window(win);

/* Return handle abstraction */
return (HWND)win;
}