#include <iostream>
#include <chrono>
#include <random>
#include <queue>
using namespace std;

int getRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

class Task {
private:
	int value;
	int priority;
	double duration_ms;
	int steps;
	int currentStep;
public:
	 Task(int a, int b, double c, int d, int e) : value(a), priority(b), duration_ms(c),
			 	 	 	 	 	 	 	 	 	  steps(d), currentStep(e) {}

	int getValue() {
		return value;
	}

	int getPriority() {
		return priority;
	}

	int getSteps() {
		return steps;
	}

	int getCurrentStep() {
		return currentStep;
	}

	void setCurrentStep(int newCurrentStep) {
		currentStep = newCurrentStep;
	}

	bool operator<(const Task& other) const {
	        return priority < other.priority;
	    }
};

class VirtualThread {
private:
	std::priority_queue<Task> tasksQueue;

public:

	priority_queue<Task>& getTasksQueue() {
		return tasksQueue;
	}

	void runStep(int threadId) {
		if (!tasksQueue.empty()) {
			Task& task = const_cast<Task&>(tasksQueue.top());
			if (task.getSteps() >= task.getCurrentStep()) {
				cout << "Виртуальный поток " << threadId << " выполняет шаг "
						<< task.getCurrentStep() << "\\" << task.getSteps()
						<< " задачи " << task.getValue() << " с приоритетом "
						<< task.getPriority() << endl;
				task.setCurrentStep(task.getCurrentStep() + 1);
			}
			else {
				cout << "Виртуальный поток " << threadId << " завершил задачу "
					 << task.getValue() << ": результат = " << (task.getValue()*task.getValue()) << '\n';
				tasksQueue.pop();
			}
		}
	}

};

class HyperThreading{
private:
	VirtualThread thread1;
	VirtualThread thread2;

public:
	void execute() {
		for (int i = 0; i < 3; i++) {
			thread1.getTasksQueue().emplace(getRandomNumber(1, 50), getRandomNumber(1, 10),
					getRandomNumber(200, 1000), getRandomNumber(2, 5), 1);
			thread2.getTasksQueue().emplace(getRandomNumber(1, 50), getRandomNumber(1, 10),
								getRandomNumber(200, 1000), getRandomNumber(2, 5), 1);
		}

		while (!thread1.getTasksQueue().empty() || !thread2.getTasksQueue().empty()) {
			thread1.runStep(1);
			thread2.runStep(2);
		}
	}


};

int main() {
	HyperThreading hyperThreading;
	hyperThreading.execute();
	return 0;
}
