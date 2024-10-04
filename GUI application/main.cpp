#include <graphics.h>
#include <bits/stdc++.h>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#define PI 3.1416
#include "timer.cpp"
#include "clock.cpp"
#include "alarm.cpp"
#include "todo.cpp"

using namespace std;

void initGraphics() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
}


void topViewOfMain(){
    cleardevice();
    setbkcolor(COLOR(230, 230, 250)); // Light lavender background
    cleardevice();
    setcolor(COLOR(75, 0, 130)); // Indigo text color
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()/2 - 200, 50, (char*)"WELCOME TO Time Management App");
}

void drawMenuOption(int y, const char* text) {
    setfillstyle(SOLID_FILL, COLOR(176, 196, 222)); // Light steel blue buttons
    bar(getmaxx()/2 - 100, y, getmaxx()/2 + 100, y + 40);
    setcolor(COLOR(25, 25, 112)); // Midnight blue text
    outtextxy(getmaxx()/2 - 80, y + 10, (char*)text);
}

void solve(){
    initGraphics();
    while (true) {
        topViewOfMain();

        drawMenuOption(150, "1.Todo List");
        drawMenuOption(200, "2.Alarm");
        drawMenuOption(250, "3.Timer");
        drawMenuOption(300, "4.Clock");
        drawMenuOption(350, "5.Exit");

        outtextxy(getmaxx()/2 - 100, 400, (char*)"Click on an option to select");

        int x, y;
        while (!ismouseclick(WM_LBUTTONDOWN)) {
            delay(100);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);

        if (x > getmaxx()/2 - 100 && x < getmaxx()/2 + 100) {
            if (y > 150 && y < 190) mainOfTodo();
            else if (y > 200 && y < 240) mainOfAlarm();
            else if (y > 250 && y < 290) mainOfTimer();
            else if (y > 300 && y < 340) {
                mainOfClock();
                delay(2000);
            }
            else if (y > 350 && y < 390) exit(1);
        }
    }
}

int main(){
    solve();
    closegraph();
    return 0;
}

