
int ID;
// Custom type todo which has two fields id and task

struct todo {
    int id;
    string task;
};

//Top view
void topView(){
    cout<<"\t\t\t***********************************************************************"<<endl;
    cout<<"\t\t\t                                                                        "<<endl;
	cout<<"\t\t\t                       WELLCOME TO Your TODO List                       "<<endl;
    cout<<"\t\t\t                                                                        "<<endl;
    cout<<"\t\t\t***********************************************************************"<<endl<<endl<<endl;
}

// Add New Task Method
void addTodo() {
    system("cls");
    topView();
    todo todo;
    cout << "\n\tEnter new task : ";
    cin.get();
    getline(cin, todo.task);
    ID++;

    // Write this task to the todo.txt file
    ofstream write;
    write.open("todo.txt", ios::app);
    write << "\n" << ID;
    write << "\n" << todo.task ;
    write.close();

    //write the id to a new file so that we can use this id later to add new task
    write.open("id.txt");
    write << ID;
    write.close();

    char ch;
    cout<<"\n\tDo you want to add more task? y or n : "; cin>> ch;


    //if user wants to add a new task again then call the same function else return
    if(ch == 'y'){
        addTodo();
    }
    else{
        cout << "\n\tTask has been added successfully";
        return;
    }
}

// Display Added Tasks Method
void print(todo s) {
    cout << "\n\tID is : " << s.id;
    cout << "\tTask is : " << s.task;
}

// Read Added Tasks from todo.txt Method
void readData() {
    system("cls");
    topView();
    todo todo;
    ifstream read;
    read.open("todo.txt");
    cout << "\n\t\t\t------------------Your current Tasks in the list--------------------\n\n";

    // while we dont reach the end of file keep on printing the data on screen
    while (!read.eof()) {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        print(todo);
    }
    read.close();
}
// Search for a specific task from the todo.txt file Method
int searchData() {
    system("cls");
    topView();
    readData();
    int id;
    cout << "\n\tEnter task id : ";
    cin >> id;
    todo todo;
    ifstream read;
    read.open("todo.txt");
    // while we dont reach end of file keep or searching for the id to match to the user input id
    while (!read.eof()) {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        if (todo.id == id) {
            print(todo);
            return id;
        }
    }
    return -100;
}
// storing data for graph
void storeData(int data){
    string dataFile = "dataOfAccomplishmnet.txt";
//    ofstream outFile(dataFile, ios::app);//// Using ios::app to append data if the file exists
    ofstream outFile(dataFile.c_str(), ios::app);
	if(!outFile){
        cout << "Error creating or opening file: " << dataFile;
    }
    outFile << data << endl;
    outFile.close();


}
// Delete Task Method
void deleteData() {
    system("cls");
    topView();
    int id = searchData();
    if(id == -100){
        system("cls");
        topView();
        cout << "\n\tRecord not deleted / found\n";
        return;
    }

    cout << "\n\n\tDo you want to delete this task? y or n : ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        cout << "\n\tHow much did you accomplish?(in the scale of 10)\n";
        int accomplishPercent;
        cout << "\t";
        cin >> accomplishPercent;
        storeData(accomplishPercent);
        todo todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");
        // while we dont reach the end of file keep on searching for the id to delete the task
        while (!read.eof()) {
            read >> todo.id;
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id) {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << todo.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\n\tTask deleted successfuly";
        system("cls");
        topView();
    }
    else {
        cout << "\n\tRecord not deleted";
    }
}

void showGraph(){
    vector<int> AccomplishedData;
    int data;
    ifstream read;
    read.open("dataOfAccomplishmnet.txt");

    // while we dont reach the end of file keep on printing the data on screen
    while (read>>data) {
        AccomplishedData.push_back(data);
        if(AccomplishedData.size()>10)
            AccomplishedData.pop_back();
    }
    read.close();

    cout << "\n\n\n\tTrack of latest 10 tasks(at most):\n\n";
    for (int row = 10; row > 0; --row) {
        cout << "\t|";
//        for (int value : AccomplishedData) {
        for(int i=0; i< AccomplishedData.size(); i++){
			int value = AccomplishedData[i];
		    if (value >= row) {
                cout << "* ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    cout << "\t";
    for (int i = 0; i < AccomplishedData.size(); ++i) {
        cout << "--";
    }
    cout << endl;

    // Print the indices (X-axis labels)
    cout << "\t";
    for (int i = 1; i <= AccomplishedData.size(); ++i) {
        cout << " " << i ;
    }
    cout << endl;
    cout << "\n\n\tX-axis: Sequence of latest task\n\tY-axis: Task accomplished(%)\n";
}

void mainOfTodo()
{
    system("cls");
    topView();
	system("Color EC"); // "Color XY", X - backgroung color, Y - text color
    ifstream read;
    read.open("id.txt");
    if (!read.fail()) {
        read >> ID;
    }
    else {
        ID = 100;
    }
    read.close();

    while (true) {
        cout<<endl<<endl;
        cout << "\n\t1.Add A Task";
        cout << "\n\t2.See all tasks";
        cout << "\n\t3.Mark a task completed";
        cout << "\n\t4.Show my accomplish rate";
        cout << "\n\t5.Go back";

        int choice;
        cout << "\n\n\n\tEnter choice : ";
        cin >> choice;
        switch (choice) {
        case 1:
            addTodo();
            break;
        case 2:
            readData();
            break;
        case 3:
            deleteData();
            break;
        case 4:
            showGraph();
            break;
        case 5:
        	solve();
        	break;
        default:{
                system("cls");
                topView();
                cout<<"Enter Choice between 1 to 4";

            }
        }
    }
}

