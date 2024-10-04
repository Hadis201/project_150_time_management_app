void setTimer(int seconds);
void ringAlarm();
void topViewOfTimer(){
    cout<<"\t\t\t ***********************************************************************"<<endl;
    cout<<"\t\t\t                                                                       "<<endl;
	cout<<"\t\t\t                          WELLCOME To Timer                            "<<endl;
    cout<<"\t\t\t                                                                       "<<endl;
    cout<<"\t\t\t ***********************************************************************"<<endl<<endl<<endl;
}

void mainOfTimer() {
	system("cls");
    topViewOfTimer();
	system("Color EC");
    int seconds; 
    cout << "\n\tEnter the number of seconds to set the alarm: ";
	cin >> seconds;
	
	setTimer(seconds);
	char choice;
	cout << "\n\tType * to go back ";
	cin >> choice;
	if(choice == '*')
		solve();

}

void setTimer(int seconds) {
    std::cout << "\tAlarm set for " << seconds << " seconds." << std::endl;

    // Sleep for the specified number of seconds
    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    ringAlarm();
}

void ringAlarm() {
    std::cout << "\n\t** ALARM **" << std::endl;
    std::cout << "\tTime's up!" << std::endl;

    // Make the alarm sound (console beep)
    for (int i = 0; i < 7; ++i) {
//    	Beep(1000,1000);
        std::cout << '\a';  // Beep sound (on supported consoles)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Delay between beeps
    }
}


