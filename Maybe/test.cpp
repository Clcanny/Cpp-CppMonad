template <template<class> class Monad, class T>
const Monad<const T> inject(const T v);

template <class T>
class Maybe
{
};

template <template<class> class Monad = Maybe, class T>
const Monad<const T> inject(const T v)
{
    return Monad<const T>();
}

int main()
{
    inject<Maybe, int>(2);
}
