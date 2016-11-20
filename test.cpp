template <class T>
class A
{
    public:
        const T value;
        
    public:
        A(const T v): value(v) {}
        static const A<const T> create(const T v)
        {
            return A(v);
        }
};

int main()
{
    A<const int> a = A<const int>::create(2);
}
