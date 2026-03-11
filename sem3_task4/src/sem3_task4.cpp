#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

class TaskTimer
{
private:
	time_point<high_resolution_clock> start_time;
	time_point<high_resolution_clock> end_time;

public:
	void start(){
		start_time = high_resolution_clock::now();
	}

	void stop() {
		end_time = high_resolution_clock::now();
	}

	double getDurationMs() const {
		return duration<double, milli>(end_time - start_time).count();
	}

	void measureSorting(vector<int>& data) {
		start();
		sort(data.begin(), data.end());
		stop();

		printDuration();
	}

	void printDuration() const {
		double ms = getDurationMs();
		cout << "Время выполнения сортировки: " << fixed << setprecision(3) << ms << " мс\n";
	}
};

int main() {
	const size_t size = 100000;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(-1000000, 1000000);

	TaskTimer timer;

	vector<int> v(size);
	for (auto& x : v) x = dist(gen);
	timer.measureSorting(v);

	return 0;
}
