#include <iostream>
#include <chrono>
#include <boost/thread.hpp>
#include <thread>
using namespace std;

int countSum(int N) {
	int result = 0;
	for (int i = 0; i <= N; i++) {
		result += i;
	}
	return result;
}

void printTime(int N) {
	for (int i = N; i > 0; --i) {

		if (i % 10 == 0 || i % 10 >= 5 || (i % 100 >= 11 && i%100 <= 14)) {
			cout << "Осталось: " << i << " секунд" << endl;
		} else if (i % 10 >= 2) {
			cout << "Осталось: " << i << " секунды" << endl;
		} else {
			cout << "Осталось: " << i << " секунда" << endl;
		}


		if (i > 1) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	cout << "Время вышло!" << endl;
}

void printTime(std::chrono::seconds seconds) {
	auto hours = std::chrono::duration_cast<std::chrono::hours>(seconds);
	seconds -= hours;

	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(seconds);
	seconds -= minutes;

	std::cout << hours.count()   << " ч " << minutes.count() << " мин " << seconds.count() << " сек\n";
}

int main() {
	cout << "ЗАДАНИЕ 1\n";
	int N;
	cout << "Введите число: ";
	cin >> N;

	auto start = std::chrono::high_resolution_clock::now();
	int result = countSum(N);
	auto end = std::chrono::high_resolution_clock::now();

	cout << "Результат: " << result << endl;
	cout << "Время: " << std::chrono::duration<double>(end - start).count() << " секунд\n";
	cout << "\n";




	cout << "ЗАДАНИЕ 2\n";
	cout << "Введите число: ";
	cin >> N;
	printTime(N);
	cout << "\n";



	cout << "ЗАДАНИЕ 3\n";
	cout << "Введите количество секунд: ";
	cin >> N;
	auto seconds = std::chrono::seconds{N};
	printTime(seconds);


	return 0;
}
