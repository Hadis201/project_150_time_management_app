#include<bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <time.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <windows.h>
#define PI 3.1416

using namespace std;
void solve();

#include "clock.cpp"
#include "alarm.cpp"
#include "todo.cpp"
#include "timer.cpp"
using namespace std;

void topViewOfMain() {
    cout<<"\t\t\t ***********************************************************************"<<endl;
    cout<<"\t\t\t                                                                       "<<endl;
    cout<<"\t\t\t                 WELCOME TO Time Management App                        "<<endl;
    cout<<"\t\t\t                                                                       "<<endl;
    cout<<"\t\t\t ***********************************************************************"<<endl<<endl<<endl;
}
void solve() {
    system("cls");
    system("Color EC");
    system("title Time Management App");

    while (true) {
        topViewOfMain();
        cout<<endl<<endl;
        cout << "\n\t1. Todo List";
        cout << "\n\t2. Alarm";
        cout << "\n\t3. Timer";
        cout << "\n\t4. Clock";
        cout << "\n\t5. Exit";
        int choice;
        cout << "\n\n\n\tEnter choice : ";
        cin >> choice;

        switch (choice) {
            case 1:
                mainOfTodo();
                break;
            case 2:
                mainOfAlarm();
                break;
            case 3:
                mainOfTimer();
                break;
            case 4:
                mainOfClock();
                break;
            case 5:
                exit(1);
            default:
                cout<<"\tEnter Choice between 1 to 5";
        }
        system("cls");
    }
}
int main() {
    solve();
    return 0;
}
