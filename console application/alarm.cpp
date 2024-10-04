



#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;
void getTime(struct tm& askedTime);
void timeDifference(const struct tm& askedTime, struct tm& differenceInTime, time_t& now);
void startAlarm(const struct tm& askedTime);
void backgroundAlarm(const struct tm& askedTime);
void topViewOfAlarm(){
    cout<<"\t\t\t***********************************************************************"<<endl;
    cout<<"\t\t\t                                                                        "<<endl;
	cout<<"\t\t\t                       WELLCOME TO Your Alarm                           "<<endl;
    cout<<"\t\t\t                                                                        "<<endl;
    cout<<"\t\t\t***********************************************************************"<<endl<<endl<<endl;
}
int mainOfAlarm() {
    system("cls");
    topViewOfAlarm();
    
    struct tm askedTime = {};
    getTime(askedTime);
    
    // Start the alarm in a separate thread
    std::thread alarmThread(backgroundAlarm, askedTime);
    alarmThread.detach();  // Detach the thread to run independently
	char choice;
	cout << "\n\t*.Back\n\t";
	cin >> choice;
	if(choice == '*')
		solve();
    // Continue with other tasks in the app
//    std::cout << "You can continue with other tasks..." << std::endl;
//
//    // Example of other tasks
//    while (true) {
//        std::string task;
//        std::cout << "Enter a task (or type 'exit' to quit): ";
//        std::cin >> task;
//        if (task == "exit") break;
//        std::cout << "Task '" << task << "' is being processed..." << std::endl;
//    }

    return 0;
}

void getTime(struct tm& askedTime) {
    std::string timeInput;
    std::cout << "\tEnter time in 24-hour format [HH:MM]: ";
    std::cin >> timeInput;

    int hour, minute;
    std::stringstream ss(timeInput);
    char colon;

    ss >> hour >> colon >> minute;

    time_t now = time(0);
    struct tm* currentTime = localtime(&now);

    askedTime = *currentTime;
    askedTime.tm_hour = hour;
    askedTime.tm_min = minute;
    askedTime.tm_sec = 0;
}

void timeDifference(const struct tm& askedTime, struct tm& differenceInTime, time_t& now) {
    time_t askedTimeT = mktime(const_cast<struct tm*>(&askedTime));
    int seconds = difftime(askedTimeT, now);

    if (seconds < 0) {
        // If the time difference is negative, it means the asked time is for the next day.
        seconds += 24 * 3600;  // Add 24 hours in seconds
    }

    differenceInTime.tm_hour = seconds / 3600;
    differenceInTime.tm_min = (seconds % 3600) / 60;
    differenceInTime.tm_sec = seconds % 60;
}

void backgroundAlarm(const struct tm& askedTime) {
    struct tm differenceInTime;

    while (true) {
        time_t now = time(0);
        timeDifference(askedTime, differenceInTime, now);

        if (differenceInTime.tm_hour == 0 && differenceInTime.tm_min == 0 && differenceInTime.tm_sec == 0) {
            std::cout << std::endl << "\tTime Completed" << std::endl;
            for(int i=0; i<=7; i++) {
                std::cout << '\a';  // Beep sound (on supported consoles)
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

