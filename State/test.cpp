#include <boost/mpl/placeholders.hpp>

template <class T>
class TEST
{};

int main()
{
    typedef TEST<boost::mpl::placeholders::_1> T;
    T t;
}
