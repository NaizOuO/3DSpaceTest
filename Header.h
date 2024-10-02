#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<ctime> 
#include<stdlib.h>
using namespace std;

inline void SetColor(int color);
inline void gotoxy(int* x, int* y);
inline void getxy(int* x,int* y);
inline void delay(int time);
inline void point(int w,int h,int x,int y,char c);
inline void drawScreen(int w, int h);
inline void showLine(int w, int h, int x0, int y0, int x1, int y1, int c);

inline void SetColor(int color)
{
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole,color);
}

inline void gotoxy(int x, int y) {
	COORD p = {x,y};
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, p);
}

inline void getxy(int* x,int* y) {
	CONSOLE_SCREEN_BUFFER_INFO c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &c);
	*x =c.dwCursorPosition.X;
	*y =c.dwCursorPosition.Y;
}

inline void delay(int time){
	clock_t now=clock(); 
	while(clock()-now<time); 
} 

inline void point(int w,int h,int x,int y,char c){
	x=x+w/2;y=h/2-y;
	if(y>0&&y<h&&x>0&&x<w){
		gotoxy(x,y);
		cout<<c;
	}
}

inline void drawScreen(int w, int h, int c){
	for(int i = -(w/2-1); i <= (w/2-1); i++){
		if(i == -(w/2-1) || i == (w/2-1)){
			for(int j = -(h/2-1); j <= (h/2-1); j++){
				point(w,h,i,j,c);
			}
		}
		point(w,h,i,-(h/2-1),c);
		point(w,h,i,(h/2-1),c);
	}
}

inline void showLine(int w, int h, int x0, int y0, int x1, int y1, int c){		//from ST7920_SPI-master
	int dx = abs(x1-x0);
	int dy = abs(y1-y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	 
	while(1) {
		point(w, h, x0, y0, c);
		if(x0==x1 && y0==y1) return;
		int err2 = err+err;
		if(err2>-dy) { err-=dy; x0+=sx; }
		if(err2< dx) { err+=dx; y0+=sy; }
	}
}
