#include <iostream>


// C++98
template<int N>
struct Factorial
{
    static const int result = N * Factorial<N - 1>::result;
};

template<>
struct Factorial<0>
{
    static const int result = 1;
};


// C++11
constexpr unsigned fact(unsigned N) {
    return (N == 0) ? 1 : N * fact(N - 1);
}

// C++11
// value-based metaprogramming
constexpr unsigned fib(unsigned N) {
    return (N < 2) ? 1 : fib(N - 2) + fib(N - 1);
}


// C++11
// template-based metaprogramming
template<unsigned N>
constexpr unsigned fib2 = fib2<N - 2> + fib2<N - 1>;

template<>
constexpr unsigned fib2<0> = 1;

template<>
constexpr unsigned fib2<1> = 1;


///////////////////////////

struct nil {
};

template<class H, class T = nil>
struct cons {
    typedef H head;
    typedef T tail;
    typedef cons<int, cons<std::string, cons<double, cons<float>>>> typeList;
};

template<class TL>
void print() {
    std::cout << typeid(typename TL::head).name() << std::endl;
    print<typename TL::tail>();
}

template<>
void print<nil>() {
}

int main() {
    // C++98
    Factorial<5> fac;
    std::cout << "Factorial of 5: " << fac.result << std::endl;

    // C++11
    std::cout << "Factorial of 10: " << fact(10) << std::endl;

    std::cout << "Fibonacci of 9: " << fib(9) << std::endl;

    std::cout << "Fibonacci of 12: " << fib2<12> << std::endl;
    
    print<cons<int, cons<char>>>();
    print<cons<nil>::typeList>();

    return 0;
}