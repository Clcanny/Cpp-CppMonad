//maybem.h
//
//The Maybe monad.
//Adds monadic behaviour to Maybe.  Allows you to sequence a number of
//operations of type Maybe<a>, and drop out at the first point of failure.

#pragma once

#include "monad.h"
#include "maybe.h"

template<> struct Monad<Maybe>
{
	template<typename a> static const Maybe<a> unit (a value)
	{
		return Just(value);
	}
};

template<typename a, typename b>
auto operator>>=(const Maybe<a>&& in, const b&& f) -> decltype(f(in.fromJust()))
{
	typedef decltype(f(in.fromJust())) maybeType;
	return in.isJust() ? f(in.fromJust()) : maybeType::Nothing();
}
