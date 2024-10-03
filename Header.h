#include <iostream>
#include <windows.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <conio.h>

// Function prototypes
inline void gotoxy(short int x, short int y);
inline void drawScreen(int w, int h, int c);
inline void point(int w, int h, int x, int y, char c);
inline void showLine(int w, int h, int x0, int y0, int x1, int y1, int c);
inline void adjustCoordinates(int &x, int &y, int w, int h);

// Function implementations
// 設置光標位置 / Set cursor position
inline void gotoxy(short int x, short int y) {
    COORD p = {x, y};
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, p);
}

// 座標系轉換 / Adjust coordinates
inline void adjustCoordinates(int &x, int &y, int w, int h) {
    x = x + w / 2;
    y = h / 2 - y;
}

// 繪製點 / Draw point
inline void point(int w, int h, int x, int y, char c) {
    adjustCoordinates(x, y, w, h);
    if (y > 0 && y < h && x > 0 && x < w) { 
        gotoxy(x, y);
        std::cout << c;
    }
}

// 繪製直線 / Draw line (from ST7920_SPI-master)
inline void showLine(int w, int h, int x0, int y0, int x1, int y1, int c) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    while (true) {
        point(w, h, x0, y0, c);
        if (x0 == x1 && y0 == y1) return;
        int err2 = err + err;
        if (err2 > -dy) { err -= dy; x0 += sx; }
        if (err2 < dx) { err += dx; y0 += sy; }
    }
}

// 繪製畫面 / Draw screen
inline void drawScreen(int w, int h, int c) {
    showLine(w, h, -w / 2 + 1, h / 2 - 1, w / 2 - 1, h / 2 - 1, c);
	showLine(w, h, -w / 2 + 1, h / 2 - 1, -w / 2 + 1, -h / 2 + 1, c);
	showLine(w, h, w / 2 - 1, h / 2 - 1, w / 2 - 1, -h / 2 + 1, c);
	showLine(w, h, -w / 2 + 1, -h / 2 + 1, w / 2 - 1, -h / 2 + 1, c);
}
