#include <iostream>
#include <vector>
#include <string>

class VirtualThread {
private:
    std::vector<std::string> tasks;
    size_t nextTask = 0;
    std::string currentTask = "";

public:
    void addTask(const std::string& task) {
        tasks.push_back(task);
    }

    bool hasTasks() const {
        return nextTask < tasks.size();
    }

    std::string getCurrentTask() {
    	return currentTask;
    }

    void startNext(int threadId) {
        if (nextTask >= tasks.size()) return;

        currentTask = tasks[nextTask];
        nextTask++;
        std::cout << "Виртуальный поток " << threadId << " начал " << currentTask << "\n";
    }

    void finish(int threadId) {
        if (currentTask.empty()) return;

        std::cout << "Виртуальный поток " << threadId << " закончил " << currentTask << "\n";
        currentTask = "";
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread vt1;
    VirtualThread vt2;

public:
    HyperThreadingSimulator() {
        std::vector<std::string> allTasks = {"задачу A", "задачу B", "задачу C", "задачу D"};

        for (size_t i = 0; i < allTasks.size(); ++i) {
            if (i % 2 == 0) {
            	vt1.addTask(allTasks[i]);
            }
            else {
            	vt2.addTask(allTasks[i]);
            }
        }
    }

    void execute() {
        while (vt1.hasTasks() || vt2.hasTasks()) {

            vt1.startNext(1);
            vt2.startNext(2);

            vt1.finish(1);
            vt2.finish(2);
        }

        std::cout << "\nВсе задания выполнены!\n";
    }
};

int main() {
    HyperThreadingSimulator simulator;
    simulator.execute();
    return 0;
}
