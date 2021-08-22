#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <list>
#include <forward_list>
#include <algorithm>
#include <string>


template<typename T>
bool check_forward_iterator = std::is_same<std::iterator_traits<typename T::iterator>::iterator_category, 
	std::forward_iterator_tag>::value;


int main() {
	std::vector<int> vec = { 1,2,3,5,4,8,6,3 };

	std::ostream_iterator<int> it = { std::cout, "::" };
	//std::ostream_iterator<int> it(std::cout, "::");	equal to the line above

	for (auto i : vec) {
		*it++ = i;
	}

	std::cout << std::endl;

	std::istringstream bytes("20 20 50 30 2 4 5 6 9 8 7");
	std::vector<int> bar{ std::istream_iterator<int>(bytes), std::istream_iterator<int>() };

	for (auto i : bar) {
		*it++ = i;
	}

	std::cout << std::endl;
	std::cout << std::boolalpha << check_forward_iterator<std::forward_list<int>> << std::endl;
	std::cout << std::boolalpha << check_forward_iterator<std::list<int>> << std::endl;

	auto it_1 = vec.begin();
	auto it_2 = vec.begin() + 4;
	std::cout << "first value: " << *(it_1) << std::endl;
	std::cout << "third value: " << *(it_1 + 2) << std::endl;
	std::cout << "Distance: " << std::distance(it_1, it_2) << std::endl;

	std::advance(it_1, 4);
	std::cout << "Distance: " << std::distance(it_1, it_2) << std::endl;

	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, "::"});

	std::cout << std::endl;

	std::cout << "counting 3: " << std::count(vec.begin(), vec.end(), 3) << std::endl;
	std::cout << "counting >5: " << std::count_if(vec.begin(), vec.end(), [](const int e) { return e > 5; }) << std::endl;

	std::cout << std::endl;

	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, "::"});
	vec.erase(std::remove(vec.begin(), vec.end(), 3));
	std::cout << std::endl;
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, "::"});
	std::cout << std::endl;

	std::string text = "SomeText Aaaaa";
	std::cout << text << std::endl;
	std::transform(text.begin(), text.end(), text.begin(), std::toupper);
	std::cout << text << std::endl;

	std::reverse(text.begin(), text.end());
	std::cout << text << std::endl;

	vec = {1, 2, 3};

	while (std::next_permutation(vec.begin(), vec.end())) {
		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, ", "});
		std::cout << std::endl;
	}

	return 0;
}