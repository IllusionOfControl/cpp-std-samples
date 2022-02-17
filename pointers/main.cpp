#include <iostream>
#include <vector>


/*
* Types of pointers:
*	+ referenceless type (A)
*	+ lvalue-pointer (A&)
*	+ rvalue-pointer (A&&)
* 
* Rules for lvalue:
*	+ Name of variable or argument (even if they type is rvalue-pointer). For example: std::cin.
*	+ Call a function or operator with the return type is lvalue-pointer. For example: std::cout << 1, ++it.
*	+ String literals. For example: "Hello, world!".
* 
* Rules for rvalue:
*	+ Non-String literals. For example: 42, true, nullptr.
*	+ Call function or operaor with the return type is not pointer.
*	+ Taking address: &a.
*	+ Call a function or operator with the return type is lvalue-pointer. For example: std::move(x).
*   + a.m, where a — rvalue.
*/

/*
* Ways of initialization
*	+ T& x = lvalue
*		usual pointer
*	+ T& x = rvalue
*		only for const pointer: const T& x = rvalue;
*	+ T&& x = lvalue
*		you can't do that
*	+ T&& x = rvalue
*		string(const string&);
*		string(string&&);
*		string s1 = "Hello ";
*		string s2 = "world!";
*		string s3 = s1 + s2;	// s1 + s2 is rvalue
* 
*	|-------|			|-------|
*	|  T&&	|<-----*----|rvalue	|
*	|-------|      |    |-------|
*                  |
*                  | only dor const T&
*				   |	or VisualStudio
*                  |
*	|-------|	  \|/	|-------|
*	|  T&&	|<-----*----|rvalue	|
*	|-------|			|-------|
* 
*/

/*
*	https://habr.com/ru/post/322132/
*/


void fill(std::vector<int> numbers) {
	// nothing
}

void setNumbers(std::vector<int> numbers) {
	//nothing
}

void message(const int& num) {
	std::cout << "lvalue" << std::endl;
}

void message(int&& num) {
	std::cout << "rvalue" << std::endl;
}

template<class T>
void nothing_do_xvalue(T&& rvalue) {

}

int main() {
	std::vector<int> numbers(1000000);
	fill(numbers);					// copy vector
	setNumbers(std::move(numbers));	// move vector

	// str is lvalue, but std::string is rvalue :/
	std::string&& str = std::string("Hello");
	std::string* psrt = &str;

	int a = 10;
	message(a);				// lvalue
	message(std::move(a));	// rvalue
	message(20);			// rvalue

	nothing_do_xvalue(42);
	nothing_do_xvalue(a);
	nothing_do_xvalue("hello lvalue");

	char&& t = 'a';	//lvalue
}