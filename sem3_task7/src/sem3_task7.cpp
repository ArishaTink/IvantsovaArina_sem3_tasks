#include <iostream>
#include <vector>
#include <string>

using namespace std;

class VirtualThread {
private:
    std::vector<int> numbers;
    std::vector<int> queue;

public:
    void setNumbers(std::vector<int> newNumbers) {
    	numbers = newNumbers;
    }

    std::vector<int> getNumbers() {
    	return numbers;
    }

    void addQueue(int newQueue) {
    	queue.push_back(newQueue);
    }

    std::vector<int> getQueue() {
    	return queue;
    }


    int run(int number) {
    	if (number == 1) {return number;}
    	return number*run(number-1);
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread vt1;
    VirtualThread vt2;

public:
    HyperThreadingSimulator() {
        std::vector<int> numbers = {5, 7, 10, 12};
        vt1.setNumbers(numbers);
        vt2.setNumbers(numbers);

        for (size_t i = 0; i < numbers.size(); ++i) {
            if (i % 2 == 0) {
            	vt1.addQueue(i);
            }
            else {
            	vt2.addQueue(i);;
            }
        }
    }

    void execute() {
        for(int i = 0; i < 2; i++) {

        	int number1 = vt1.getNumbers()[vt1.getQueue()[i]];
        	int number2 = vt2.getNumbers()[vt2.getQueue()[i]];

            int factorial1 = vt1.run(number1);
            int factorial2 = vt2.run(number2);

            cout << "Виртуальный поток 1 вычисляет " << number1 << "! = " << factorial1 << "\n";
            cout << "Виртуальный поток 2 вычисляет " << number2 << "! = " << factorial2 << "\n";
        }

        cout << "\nВсе задания выполнены!\n";
    }
};

int main() {
    HyperThreadingSimulator simulator;
    simulator.execute();
    return 0;
}
