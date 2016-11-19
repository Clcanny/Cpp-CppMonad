# Monadic operations in C++

This began as a further attempt to implement the Maybe monad in C++, but quickly
spiralled out of control and now includes an implementation of the List monad as
well (using std::list!).  This is really for my own amusement rather than to try
and do anything useful with them.  It also gave me an excuse to try out C++ 11
lambda functions for the first time.

My original implementation defined a macro called `MBind` which caused a number
of problems -- thankfully [PJayB][pjayb] managed to find a way around that so
this version uses C++ lambdas directly (take a look at the changelog if you want
to see the changes made).

Please bear in mind I made this purely out of curiosity -- I realise a lot of
this is pathological in C++.

I've also included the equivalent Haskell code, so you can see what I based the
syntax on.  In Haskell you'd probably use `do` syntax for a case like this, but
I stuck with manually binding lambda functions so the similarity with the C++ is
more obvious.

Next up... The State monad!

[pjayb]: https://gist.github.com/PJayB
