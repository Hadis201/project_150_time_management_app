#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <iostream>
#define PI 3.1416
using namespace std;

void drawClock() {
    // Initialize graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    if (graphresult() != grOk) {
        cout << "Graphics initialization failed!" << endl;
        cout << "Press any key to continue..." << endl;
        getch();
        return;
    }

    while (!kbhit()) {  // Run until a key is pressed
        cleardevice();
        // Draw clock face
        setcolor(WHITE);
        circle(getmaxx()/2, getmaxy()/2, 200);  // Outer circle
        circle(getmaxx()/2, getmaxy()/2, 5);    // Center point

        // Get current time
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Draw hour markers
        for (int i = 1; i <= 12; i++) {
            double angle = i * PI / 6 - PI / 2;
            int x1 = getmaxx()/2 + 180 * cos(angle);
            int y1 = getmaxy()/2 + 180 * sin(angle);
            int x2 = getmaxx()/2 + 150 * cos(angle);
            int y2 = getmaxy()/2 + 150 * sin(angle);
            line(x1, y1, x2, y2);
        }

        // Hour hand
        double hourAngle = (ltm->tm_hour % 12 + ltm->tm_min / 60.0) * PI / 6 - PI / 2;
        int hourX = getmaxx()/2 + 100 * cos(hourAngle);
        int hourY = getmaxy()/2 + 100 * sin(hourAngle);
        setcolor(LIGHTBLUE);
        line(getmaxx()/2, getmaxy()/2, hourX, hourY);

        // Minute hand
        double minuteAngle = ltm->tm_min * PI / 30 - PI / 2;
        int minuteX = getmaxx()/2 + 140 * cos(minuteAngle);
        int minuteY = getmaxy()/2 + 140 * sin(minuteAngle);
        setcolor(LIGHTGREEN);
        line(getmaxx()/2, getmaxy()/2, minuteX, minuteY);

        // Second hand
        double secondAngle = ltm->tm_sec * PI / 30 - PI / 2;
        int secondX = getmaxx()/2 + 160 * cos(secondAngle);
        int secondY = getmaxy()/2 + 160 * sin(secondAngle);
        setcolor(LIGHTRED);
        line(getmaxx()/2, getmaxy()/2, secondX, secondY);

        // Display digital time
        char timeStr[9];
        sprintf(timeStr, "%02d:%02d:%02d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        setcolor(YELLOW);
        outtextxy(getmaxx()/2 - 50, getmaxy()/2 + 220, timeStr);

        // Instructions
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(getmaxx()/2 - 110, getmaxy() - 25, "Press any key to return to menu");

        delay(1000);  // Wait for 1 second
    }
    closegraph();
}


int mainOfClock() {
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_HIDE);  // Hide console window

    drawClock();

    ShowWindow(consoleWindow, SW_SHOW);  // Show console window again
    system("cls");// Clear console screen
    return 0;
}
