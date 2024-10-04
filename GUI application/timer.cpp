#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>

void setTimer(int seconds);
void input_text(int x, int y, char* str, int maxlen);

void topViewOfTimer(){
    cleardevice();
    setbkcolor(COLOR(230, 230, 250)); // Light lavender background
    cleardevice();
    setcolor(COLOR(75, 0, 130)); // Indigo text color
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()/2 - 150, 50, (char*)"WELCOME To Timer");
}

void mainOfTimer() {
    topViewOfTimer();
    char seconds_str[10];
    outtextxy(50, 150, (char*)"Enter the number of seconds to set the timer:");
    input_text(50, 180, seconds_str, 10);
    int seconds = atoi(seconds_str);

    setTimer(seconds);
    outtextxy(40, 250, (char*)"Timer completed. Press any key to go back");
    getch();
}

void setTimer(int seconds) {
    char msg[50];
    sprintf(msg, "Timer set for %d seconds.", seconds);
    outtextxy(50, 220, msg);

    for (int i = seconds; i > 0; i--) {
        cleardevice();
        topViewOfTimer();
        char timeLeft[20];
        sprintf(timeLeft, "Time left: %d seconds", i);
        outtextxy(getmaxx()/2 - 100, getmaxy()/2, timeLeft);
        delay(1000);
    }

    cleardevice();
    topViewOfTimer();
    outtextxy(getmaxx()/2 - 40, getmaxy()/2, (char*)"Time's up!");
    for (int i = 0; i < 5; i++) {
        Beep(1000, 500);
        delay(500);
    }
}

// Note: input_text function is already defined in alarm.cpp, so we don't need to redefine it here.
