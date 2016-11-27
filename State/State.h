#ifndef State_H
#define State_H

#include "../Monad.h"

template <class S, class A>
class State
{
    private:
        const std::function<const std::tuple<const A, const S>(const S)> fn;
        
        template <class T>
        friend class Monad;
        
    public:
        State(const std::function<const std::tuple<const A, const S>(const S)> f) :
            fn(f) {};
            
        const tuple<const A, const S> runState(const S s) const
        {
            return fn(s);
        }
        const A evalState(const S s) const
        {
            return get<0>(runState(s));
        }
        const S execState(const S s) const
        {
            return get<1>(runState(s));
        }
};

template <class S>
struct StateWrapper
{
    template <class A>
    struct apply
    {
        typedef const State<const S, const A> type;
    };
};

#endif
