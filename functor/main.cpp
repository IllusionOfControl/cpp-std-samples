#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>


using namespace std;


class Functor {
public:
	void operator()() {
		cout << "Hello from functor" << endl;
	}
};

class SortFunctor {
public:
	bool operator()(int a, int b) {
		return a < b;
	}
};

int sum(int a, int b) {
	return a + b;
}

bool cmp(int a, int b) {
	return a < b;
}

int main() {
	Functor f;
	f();

	int (*func) (int a, int b);

	func = &sum;

	cout << func(10, 15) << endl;

	// function pointer

	vector<int> num_list = { 3, 5, 6, 8, 1, 7, 5, 7 };
	sort(num_list.begin(), num_list.end(), &cmp);

	for (int i : num_list) {
		cout << i << " ";
	}
	cout << endl;

	// functor

	SortFunctor sf;
	num_list = { 3, 5, 6, 8, 1, 7, 5, 7 };
	sort(num_list.begin(), num_list.end(), sf);

	for (int i : num_list) {
		cout << i << " ";
	}
	cout << endl;

	// lambda

	num_list = { 3, 5, 6, 8, 1, 7, 5, 7 };
	sort(num_list.begin(), num_list.end(), [](int a, int b) {
		return a < b;
	});

	for (int i : num_list) {
		cout << i << " ";
	}
	cout << endl;

}