#include <functional>
#include <iostream>

/* data Exp = Const Integer */
/*          | Plus Exp Exp */
/*          | Times Exp Exp */
/*          | Arg1 */
/*          | Arg2 */

template<int n> struct Const {};

template<class E1, class E2>
struct Plus {};

template<class E1, class E2>
struct Times {};

struct Arg1 {};
struct Arg2 {};

/* type Args = [Integer] */
struct Args
{
    Args(int i, int j)
    {
        _a[0] = i;
        _a[1] = j;
    }
    int operator[](int n)
    {
        return _a[n];
    }
    int _a[2];
};

/* newtype Prog t = PR (Args -> t) */
template<class T> struct PR
{
    T operator()(Args args);
};

template<int n>
struct GetArg   // instance of the concept PR
{
    int operator()(Args args)
    {
        return args[n];
    }
};

template<class P1, class P2> // compile-time type parameters
struct Bind
{
    Bind(P1 prog, std::function<P2(int)> cont)
        : _prog(prog), _cont(cont)
    {}
    P1 _prog;
    std::function<P2(int)> _cont;
    int operator()(Args args)
    {
        int v = _prog(args);
        P2 prog2 = _cont(v);
        return prog2(args);
    }
};

struct Return
{
    Return(int v) : _v(v) {}
    int operator()(Args args)
    {
        return _v;
    }
    int _v;
};

template<class Exp>
struct Compile {};

template<int c>
struct Compile<Const<c> > : Return
{
    Compile() : Return(c) {}
};

template<>
struct Compile<Arg1> : GetArg<0> {};

template<class L, class R>
struct Compile<Plus<L, R> >
{
    int operator()(Args args)
    {
        return Bind<Compile<L>, Bind<Compile<R>, Return> > (
                   Compile<L>(),
                   [](int left) -> Bind<Compile<R>, Return>
        {
            return Bind<Compile<R>, Return>(
                Compile<R>(),
            [left](int right) -> Return {
                return Return(left + right);
            }
            );
        }
               )(args);
    }
};

int main()
{
    Args args(3, 4);
    Compile<Plus<Times<Arg1, Arg2>, Const<13> > > act;
    int v = act(args);
    std::cout << v << std::endl;
}
