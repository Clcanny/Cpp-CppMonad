#ifndef Header_H
#define Header_H

#include <boost/mpl/bind.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <functional>
#include <type_traits>
#include <string>
#include <cassert>

using boost::mpl::bind1;
using boost::mpl::apply_wrap1;
using boost::mpl::apply_wrap2;
using boost::mpl::placeholders::_1;
using std::function;
using std::true_type;
using std::false_type;
using std::is_same;
using std::tuple;
using std::get;
using std::string;
using std::to_string;

#endif
