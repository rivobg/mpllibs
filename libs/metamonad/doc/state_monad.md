# state monad

This is the C++ template metaprogramming equivalent of Haskell's State monad.
Monadic values are metafunctions classes taking the state as argument and
returning (value, state) pairs. The purpose of this monad is to combine such
functions.

## General information

* header: `<mpllibs/metamonad/state.hpp>`
* tag of monad: `state_tag`
* `return`'s logic: construct a constant function, returning always return's
  argument regardless of the state and leaving the state unchanged
* `bind`'s logic: construct a function that gets a value and a new state by
  passing the state to bind's first argument (which is a function mapping state
  to a (value, state) pair). The resulting value is passed to bind's second
  argument as input to construct a new monadic value (a new function expecting a
  state). This new monadic value is the result of bind.

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)


