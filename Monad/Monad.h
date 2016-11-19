#ifndef Monad_H
#define Monad_H

/* monad.h */

/* Defines the two monad operations.  Every class which wants to be treated as a */
/* monad must provide a specialization for the Monad class or a constructor which */
/* takes a single parameter of the type of the valuse it's wrapping.  As well as */
/* that, It must also overload operator>>= for binding purposes. */

template <template <typename a, typename...> class m>
struct Monad
{
    template <typename a> static m<a> unit(a value)
    {
        return m<a>(value);
    }
};

#endif
