#include <iostream>


class Anything
{
public:
    int m_value;

    Anything() { m_value = 0; }

    void resetValue() { m_value = 0; }
    void setValue(int value) { m_value = value; }

    int getValue() const { return m_value; }

    const int sum(const int *a, const int *b) const {
        return *a + *b;
    }
};

int main() {
    const int a_1(8);       // direct initialize
    const int a_2 = 5;      // copy constructor
    const int a_3 = {10};   // uniform initialize

    const Anything anything; // call default constructor 
    //anything.m_value = 7; // compile error
    //anything.setValue(7); // compile error

    anything.getValue();
    int a = 5, b = 10;
    const int result = anything.sum(&a, &b);

    int b_0 = 0;
    const int b_1 = 1;      // value const

    const int b_2 = 2;
    const int *ptr_2 = &b_2;  // pointer const
    //ptr_2 = 0;             // compile error

    int b_3 = 3;
    int* const ptr_3 = &b_3;
    //ptr_3 = &b_0;           // compile error

    int b_4 = 4;
    const int *const ptr_4 = &b_4;
    //ptr_4 = &b_0;           // compile error
    //ptr_4 = 10;             // compile error
}