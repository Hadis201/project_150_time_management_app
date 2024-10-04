#include <graphics.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <vector>
void input_text(int x, int y, char* str, int maxlen);
void showGraph();
struct todo {
    int id;
    std::string task;
};

int ID = 0;


void topView(){
    cleardevice();
    setbkcolor(COLOR(230, 230, 250)); 
    cleardevice();
    setcolor(COLOR(75, 0, 130)); 
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()/2 - 150, 50, (char*)"WELCOME TO Your TODO List");
}

void addTodo() {
    topView();
    todo newTodo;
    char taskInput[100];
    outtextxy(50, 150, (char*)"Enter new task:");
    input_text(50, 180, taskInput, 100);
    newTodo.task = std::string(taskInput);
    ID++;
    newTodo.id = ID;

    std::ofstream write("todo.txt", std::ios::app);
    write << newTodo.id << "\n" << newTodo.task << "\n";
    write.close();

    std::ofstream writeId("id.txt");
    writeId << ID;
    writeId.close();

    outtextxy(50, 250, (char*)"Task added successfully. Press any key to continue.");
    getch();
}

void readData() {
    topView();
    std::ifstream read("todo.txt");
    std::string line;
    int y = 150;
    while (std::getline(read, line)) {
        int id = std::stoi(line);
        std::getline(read, line);
        char output[150];
        sprintf(output, "ID: %d, Task: %s", id, line.c_str());
        outtextxy(50, y, output);
        y += 30;
    }
    outtextxy(50, y + 30, (char*)"Press any key to continue.");
    read.close();
    getch();
}

void deleteData() {
    topView();
    char idInput[10];
    outtextxy(50, 150, (char*)"Enter the ID of the task to delete:");
    input_text(50, 180, idInput, 10);
    int idToDelete = std::stoi(idInput);

    std::ifstream inFile("todo.txt");
    std::ofstream outFile("temp.txt");
    std::string line;
    bool found = false;
    while (std::getline(inFile, line)) {
        int id = std::stoi(line);
        std::getline(inFile, line);
        if (id != idToDelete) {
            outFile << id << "\n" << line << "\n";
        } else {
            found = true;
        }
    }
    inFile.close();
    outFile.close();

    if (found) {
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        outtextxy(50, 250, (char*)"Task deleted successfully.");
    } else {
        outtextxy(50, 250, (char*)"Task not found.");
    }
    outtextxy(50, 280, (char*)"Press any key to continue.");
    getch();
}

void showGraph() {
    topView();
    std::vector<int> accomplishData;
    std::ifstream read("dataOfAccomplishmnet.txt");
    int data;
    while (read >> data) {
        accomplishData.push_back(data);
        if (accomplishData.size() > 10) accomplishData.erase(accomplishData.begin());
    }
    read.close();

    int startX = 100, startY = 400, scale = 3;
    for (int i = 0; i < accomplishData.size(); i++) {
        setcolor(COLOR(0, 100, 0));
        rectangle(startX + i*50, startY, startX + i*50 + 40, startY - accomplishData[i]*scale);
        char label[5];
        sprintf(label, "%d", accomplishData[i]);
        outtextxy(startX + i*50 + 15, startY - accomplishData[i]*scale - 20, label);
    }
    outtextxy(50, 450, (char*)"X-axis: Sequence of latest task, Y-axis: Task accomplished(%)");
    outtextxy(50, 480, (char*)"Press any key to continue.");
    getch();
}

void mainOfTodo() {
    std::ifstream readId("id.txt");
    if (readId >> ID) {
        readId.close();
    } else {
        ID = 0;
    }

    while (true) {
        topView();
        outtextxy(50, 150, (char*)"1.Add A Task");
        outtextxy(50, 180, (char*)"2.See all tasks");
        outtextxy(50, 210, (char*)"3.Mark a task completed");
        outtextxy(50, 240, (char*)"4.Show my accomplish rate");
        outtextxy(50, 270, (char*)"5.Go back");

        outtextxy(50, 320, (char*)"Click on an option to select");

        int x, y;
        while (!ismouseclick(WM_LBUTTONDOWN)) {
            delay(100);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);

        if (x > 50 && x < 200) {
            if (y > 150 && y < 170) addTodo();
            else if (y > 180 && y < 200) readData();
            else if (y > 210 && y < 230) deleteData();
            else if (y > 240 && y < 260) showGraph();
            else if (y > 270 && y < 290) return;
        }
    }
}

