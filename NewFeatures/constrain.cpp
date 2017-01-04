#include <string>
/* g++ -std=c++1z -fconcepts constrain.cpp */

/* Declaration of the concept "EqualityComparable", which is satisfied by
 * any type T such that for values a and b of type T,
 * the expression a==b compiles and its result is convertible to bool */
template<typename T>
concept bool EqualityComparable = requires(T a, T b) {
    { a == b } -> bool;
};

void f(EqualityComparable&&) {}
/* template<typename T> */
/* void f(T&&) requires EqualityComparable<T>; // long form of the same */

int main() {
    f("abc");
    f(1);
}
