#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

class Task {
public:
    string name;
    int deadline;

    Task(string name, int deadline) : name(name), deadline(deadline) {}

    bool operator<(const Task& other) const {
        return deadline > other.deadline;
    }
};

class Scheduler {
public:
    priority_queue<Task> tasks;

    void addTask(string name, int deadline) {
        tasks.push(Task(name, deadline));
        printTasks();
    }

    Task getNextTask() {
        if (tasks.empty()) {
            throw runtime_error("No Tasks in list please add something....");
        }

        Task next_task = tasks.top();
        tasks.pop();

        return next_task;
    }

    void removeTask(string name) {
        priority_queue<Task> temp;

        while (!tasks.empty()) {
            Task task = tasks.top();
            tasks.pop();

            if (task.name != name) {
                temp.push(task);
            }
        }

        swap(tasks, temp);
        printTasks();
    }

    int simulate(vector<Task>& tasks) {
        int start_time = 0;
        int turnaround_time = 0;
        for (const Task& task : tasks) {
            int wait_time = task.deadline - start_time;
            turnaround_time += wait_time + 1;
        }
        return turnaround_time;
    }

    void printTasks() {
        priority_queue<Task> temp = tasks;
        cout << "Tasks in priority order:" << endl;
        while (!temp.empty()) {
            Task task = temp.top();
            temp.pop();
            cout << task.name << " (Deadline: " << task.deadline << ")" << endl;
        }
        cout << "---------------------------------" << endl;
    }

    void runScheduler() {
        while (true) {
            cout << "Enter the action you want to perform:" << endl;
            cout << "1. Add a task" << endl;
            cout << "2. Remove a task" << endl;
            cout << "3. Complete a task" << endl;
            cout << "0. Exit" << endl;
            cout << "Your choice: ";
            int choice;
            cin >> choice;
            cin.ignore(); 

            if (choice == 0) {
                return;
            } else if (choice == 1) {
                string name;
                int deadline;
                cout << "Enter task name: ";
                getline(cin, name);
                cout << "Enter deadline(days): ";
                cin >> deadline;
                addTask(name, deadline);
                printTasks();
            } else if (choice == 2) {
                string name;
                cout << "Enter task name to remove: ";
                getline(cin, name);
                removeTask(name);
                printTasks();
            } else if (choice == 3) {
                try {
                    Task completedTask = getNextTask();
                    cout << "Completed task: " << completedTask.name << endl;
                    printTasks();
                } catch (const runtime_error& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            } else {
                cout << "Invalid choice! Please try again." << endl;
            }
        }
    }
};

int main() {
    Scheduler scheduler;
    scheduler.runScheduler();
    return 0;
}
