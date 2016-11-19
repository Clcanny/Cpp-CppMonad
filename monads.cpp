#include <iostream>
#include <cmath>

#include "monad.h"
#include "maybem.h"
#include "listm.h"

#include "show.h"

using namespace std;

template<typename a> const Maybe<a> imSquare(a x) {
	return (abs(x) >= 0x8000) ? Maybe<a>::Nothing() : Maybe<a>::Just(x * x);
}

const Maybe<int> testMaybe()
{
	return Monad<Maybe>::unit(0x4000)  >>= [&] (const int a) {
	return imSquare(a)                 >>= [&] (const int b) {
	int c = b / a;
	return Monad<Maybe>::unit(0.5f)    >>= [&] (const float d) {
	return imSquare(c);                    };};};
}

template<typename a, typename b>
const list< pair<a, b> > cartesianProduct(const list<a> xs, const list<b> ys)
{
	return xs                          >>= [&] (const a x) {
	return ys                          >>= [&] (const b y) {
	pair<a, b> product(x, y);
	return Monad<list>::unit(product);     };};
}

const list< pair<int, int> > testList()
{
	static const int LIST_SIZE=5;

	list<int> xs_list;
	for(int i = 1; i <= LIST_SIZE; ++i)
		xs_list.push_back(i);

	list<int> ys_list;
	for(int i = 1; i <= LIST_SIZE; ++i)
		ys_list.push_back(i*i);

	return cartesianProduct(xs_list, ys_list);
}

int main(int argc, char** argv)
{
	cout << show(testMaybe()) << endl;
	cout << show(testList()) << endl;

	return 0;
}
