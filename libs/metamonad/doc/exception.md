# exception

## Synopsis

```cpp
template <class Data>
struct exception
{
  typedef exception_tag tag;

  // unspecified
};
```

## Description

Compile-time data-structure representing an error that occured during the
evaluation of template metaprograms. `Data` is a compile-time data-structure
describing the error.

## Header

```cpp
#include <mpllibs/metamonad/exception.hpp>
```

## Example

```cpp
using boost::mpl::equal_to;
using boost::mpl::int_;

struct division_by_zero;

template <class A, class B>
struct divide :
  if_<
    equal_to<A, int_<0>>,
    exception<division_by_zero>,
    divides<A, B>
  >
  {};
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)



