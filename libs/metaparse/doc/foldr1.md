# foldr1

## Synopsis

```cpp
template <class P, class State, class BackwardOp>
struct foldr1
{
  template <class S, class Pos>
  struct apply
  {
    // unspecified
  };
};
```

## Description

Parser combinator taking a parser as argument. It applies the parser on the
input string repeatedly as long as the parser accepts the input. The result of
parsing is equivalent to `boost::reverse_fold<Sequence, State, BackwardOp>`,
where `Sequence` is the sequence of the results of the applications of `P`.

When the parser rejects the input for the first time, `foldr1` rejects it as
well. At least one successful application of `P` is required for `foldr1` to
accept the input.

## Header

```cpp
#include <mpllibs/metaparse/foldr1.hpp>
```

## Expression semantics

For any `p` parser, `t` class, `f` metafunction class taking two arguments the
following are equivalent:

```cpp
foldr1<p, t, f>

mpllibs::metaparse::last_of<
  mpllibs::metaparse::look_ahead<p>,
  mpllibs::metaparse::foldr<p, t, f>
>
```

## Example

```cpp
typedef boost::mpl::list<> empty_list;
typedef boost::mpl::push_front<boost::mpl::_2, boost::mpl::_1> push_front;

template <class P>
struct any1 : foldr1<P, empty_list, push_front> {};
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)


