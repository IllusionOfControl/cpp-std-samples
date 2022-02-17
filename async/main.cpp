#include <future>
#include <iostream>
#include <vector>
#include <numeric>


int* just_return_my_int(int *a) {
	*a -= 1;
	return a;
}

void ExampleCode_1() {
	int* some_variable = new int{ 10 };
	std::future<int*> answer;

	// deffer
	answer = std::async(just_return_my_int, some_variable);
	std::cout << "After: " << *some_variable << std::endl;
	std::cout << "Answer: " << *answer.get() << std::endl;
	std::cout << "Before: " << *some_variable << std::endl;

	// async
	answer = std::async(std::launch::async, just_return_my_int, some_variable);
	std::cout << "After: " << *some_variable << std::endl;
	std::cout << "Answer: " << *answer.get() << std::endl;
	std::cout << "Before: " << *some_variable << std::endl;
}

//
//	======================================
//

void accumulate( std::vector<int>::iterator first,
				std::vector<int>::iterator last,
				std::promise<int> accumulate_promise) {
	int sum = std::accumulate(first, last, 0);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	accumulate_promise.set_value(sum);
}

void ExampleCode_2() {
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
	std::promise<int> accumulate_promise;
	std::future<int> accumulate_future = accumulate_promise.get_future();
	std::thread accumulate_thread(
		accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise)
	);
	std::cout << "Waiting future..." << std::endl;
	accumulate_future.wait();
	std::cout << "result = " << accumulate_future.get() << std::endl;
	accumulate_thread.join();
}

//
//	======================================
//


int sum(std::future<int>& fut) {
	static int sum = 69;
	sum += fut.get();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return sum;
}


void ExampleCode_3() {
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
	std::promise<int> pr;
	std::future<int> fut = pr.get_future();
	auto fur_result = std::async(sum, std::ref(fut));

	// if commented - inf waiting input value of promise
	pr.set_value(26);
	//pr.set_exception(std::make_exception_ptr(std::runtime_error("Sorry :(")));

	std::cout << "Waiting future..." << std::endl;
	std::cout << "result = " << fur_result.get() << std::endl;
}

void ExampleCode_4() {
	auto a = std::async([] {
		std::this_thread::sleep_for(std::chrono::seconds(6));
		std::cout << "first" << std::endl;
	});

	auto b = std::async([] {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::cout << "second" << std::endl;
	});
	std::cout << "main" << std::endl;
}

void ExampleCode_5() {
	std::packaged_task<int(int, int)> task([](int a, int b) {
		return (int) std::pow(a, b);
	});

	std::future<int> result = task.get_future();

	task(2, 11);

	std::cout << "Task result: " << result.get() << '\n';
}

int main() {
	ExampleCode_1();
	ExampleCode_2();
	ExampleCode_3();
	ExampleCode_4();
	ExampleCode_5();
	return 0;
}