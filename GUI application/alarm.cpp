#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <thread>
#include <chrono>
#include <string>

void input_text(int x, int y, char* str, int maxlen);
void backgroundAlarm(const struct tm& askedTime);

void topViewOfAlarm(){
    cleardevice();
    setbkcolor(COLOR(230, 230, 250)); 
    cleardevice();
    setcolor(COLOR(75, 0, 130));
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()/2 - 150, 50, (char*)"WELCOME TO Your Alarm");
}

void mainOfAlarm() {
    topViewOfAlarm();

    struct tm askedTime = {};
    char timeInput[10];
    outtextxy(50, 150, (char*)"Enter time in 24-hour format [HH:MM]:");
    input_text(50, 180, timeInput, 10);

    sscanf(timeInput, "%d:%d", &askedTime.tm_hour, &askedTime.tm_min);
    askedTime.tm_sec = 0;

    std::thread alarmThread(backgroundAlarm, askedTime);
    alarmThread.detach();

    outtextxy(50, 250, (char*)"Press any key to go back");
    getch();
//    return 0;
}

void input_text(int x, int y, char* str, int maxlen) {
    char ch = 0;
    int i = 0;
    int curr_x = x;  // Start position for text

    while (ch != 13 && i < maxlen - 1) {  // Loop until Enter (13) is pressed or max length reached
        ch = getch();  // Get the character

        if (ch == 8) {  // Backspace handling
            if (i > 0) {
                i--;
                str[i] = '\0';

                // Get the width of the last character printed
                int char_width = textwidth(&str[i]);

                // Move the cursor back and clear the character from the screen
                curr_x -= char_width;
                outtextxy(curr_x, y, (char*)" ");  // Clear the character from the screen
            }
        } else if (ch != 13) {  // If not Enter or backspace
            str[i] = ch;
            i++;

            char s[2] = {ch, '\0'};  // Create a string for the character

            // Draw the character at the current position
            outtextxy(curr_x, y, s);

            // Update the x position based on the width of the character
            curr_x += textwidth(s);
        }
    }

    str[i] = '\0';  // Null-terminate the string
}


void backgroundAlarm(const struct tm& askedTime) {
    time_t now, alarmTime;
    struct tm *currentTime;

    time(&now);
    currentTime = localtime(&now);
    alarmTime = mktime(const_cast<struct tm*>(&askedTime));

    while (difftime(alarmTime, now) > 0) {
        time(&now);
        delay(1000);
    }

    // Alarm goes off
    for (int i = 0; i < 5; i++) {
        outtextxy(getmaxx()/2 - 50, getmaxy()/2, (char*)"ALARM!");
        Beep(1000, 500);
        delay(500);
        cleardevice();
        delay(500);
    }
}
