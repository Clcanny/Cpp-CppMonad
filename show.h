//show.h
//
//Defines the "show" operation.  Defaults to using the stream operator.

#pragma once

#include <sstream>

template<typename t> std::string show(t x)
{
	std::stringstream out;
	out << x;
	return out.str();
}

template<typename a> std::string show(Maybe<a> x)
{
	if(x.isJust()) {
		std::stringstream out;
		out << "Just " << x.fromJust();
		return out.str();
	} else return "Nothing";
}

template<typename a, typename b> std::string show(std::pair<a, b> x)
{
	std::stringstream out;
	out << "(" << x.first << "," << x.second << ")";
	return out.str();
}

template<typename a> std::string show(std::list<a> x)
{
	std::stringstream out;
	out << "[";
	for(auto i = x.begin(); i != x.end(); ++i)
	{
		out << show(*i);
		if(i != --x.end())
			out << ",";
	}
	out << "]";
	return out.str();
}
