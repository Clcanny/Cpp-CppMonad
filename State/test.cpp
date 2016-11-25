#include <boost/mpl/bind.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <functional>
#include <type_traits>

using boost::mpl::bind1;
using boost::mpl::apply_wrap1;
using boost::mpl::placeholders::_1;
using std::function;
using std::true_type;
using std::false_type;
using std::tuple;
using std::get;

template <class MonadType>
struct Monad
{
    typedef false_type ImpMonad;
    
    template <class A>
    const typename apply_wrap1<MonadType, const A>::type inject(const A value);
    
    template <class A, class B>
    const typename apply_wrap1<MonadType, const B>::type bind
    (
        const typename apply_wrap1<MonadType, const A>::type a,
        function<const typename apply_wrap1<MonadType, const B>::type(const A)> b
    );
    
    template <class A, class B>
    const typename apply_wrap1<MonadType, const B>::type bind_
    (
        const typename apply_wrap1<MonadType, const A>::type a,
        const typename apply_wrap1<MonadType, const B>::type b
    )
    {
        function<const typename apply_wrap1<MonadType, const B>::type(const A)>
        fn = [&](const A)
        {
            return b;
        };
        return bind(a, fn);
    }
};

template <class S>
struct StateWrapper;

template <class S, class A>
class State
{
    public:
        const std::function<const std::tuple<const A, const S>(const S)> fn;
        
    private:
        friend class Monad<StateWrapper<S> >;
        
    public:
        State(const std::function<const std::tuple<const A, const S>(const S)> f) :
            fn(f) {};
};

template <class S>
struct StateWrapper
{
    template <class A>
    struct apply
    {
        typedef State<const S, const A> type;
    };
};

typedef bind1<StateWrapper<const char>, _1> StateChar;
template <>
struct Monad<StateChar>
{
    typedef true_type ImpMonad;
    
    template <class A>
    const typename apply_wrap1<StateChar, const A>::type inject(const A a)
    {
        const function<const tuple<const A, const char>(const char)>
        fn = [=](const char s)
        {
            return tuple<const A, const char>(a, s);
        };
        return State<const char, const A>(fn);
    }
    
    template <class A, class B>
    const typename apply_wrap1<StateChar, const B>::type bind
    (
        const typename apply_wrap1<StateChar, const A>::type a,
        const function<const typename apply_wrap1<StateChar, const B>::type(const A)> b
    )
    {
        const function<const tuple<const B, const char>(const char)> fn
            = [=](const char s)
        {
            const tuple<const A, const char> tmp = a.fn(s);
            return b.fn(get<0>(tmp)).fn(get<1>(tmp));
        };
        return State<const char, const B>(fn);
    }
};

int main()
{
    Monad<StateChar>().inject(2);
    const function<const typename apply_wrap1<StateChar, const int>::type(const int)>
    f = [](const int a)
    {
        return Monad<StateChar>().inject(a);
    };
    Monad<StateChar>().bind<const int, const int>(Monad<StateChar>().inject(2), f);
}
