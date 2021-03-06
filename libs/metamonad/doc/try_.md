# try_

## Synopsis

```cpp
template <class Expr, class... Catches>
struct try_
{
  // unspecified...
};
```

## Description

`try_` implements a compile-time try-catch block. `Expr` is a syntax, which can
be followed by any number of `catch_` and `catch_c` blocks.

`Expr` gets transformed into a monadic expression
([exception monad](exception_monad.html)) using
[`make_monadic`](make_monadic.html), thus any subexpression returning an
exception stops the evaluation of the expression and the exception gets
propagated.

A `catch_` block looks like the following:

```cpp
template <class Name, class Pred, class Body>
struct catch_
{
  // unspecified...
};
```

The name `Name` can be used in `Pred` and in `Body`, which are syntaxes. `Pred`
is evaluated and when it returns true, `Body` is evaluated and that will be the
result of the `try_` call.

A `catch_c` block is similar to a `catch_` block, but `Pred` and `Body` are
angle-bracket expressions and not syntaxes.

When multiple `catch_` and `catch_c` blocks are provided, the first one whose
predicate accepts the exception gets selected and the rest get skipped.

When a catch block throws, the exception gets propagated out of the `try_` call.
It can not be handled by catch blocks following the one that throws.

## Header

```cpp
#include <mpllibs/metamonad/try.hpp>
```

## Expression semantics

For any `f` angle-bracket expression, where `make_monadic<exception_tag, f>`
evaluates to `exception<e>` for some `e` class, `g` angle-bracket expression
where `make_monadic<exception_tag, g>` does not evaluate to an exception,
`n > 0`, `e1`, ..., `en` variables, `p1`, ..., `pn` angle-bracket expression
evaluating to a boolean value and `b1`, ..., `bn` angle-bracket expressions,
when `p1` ... `p(k-1)` evaluates to false and `pk` evaluates to true for some
`1 <= k <= n` the following are equivalent:

```cpp
try_<
  syntax<g>,
  catch_<e1, syntax<p1>, syntax<b1>>,
  // ...
  catch_<en, syntax<pn>, syntax<bn>>
>::type
make_monadic<exception_monad, g>::type
```

```cpp
try_<
  syntax<f>,
  catch_<e1, syntax<p1>, syntax<b1>>,
  // ...
  catch_<en, syntax<pn>, syntax<bn>>
>::type
eval_let<ek, syntax<e>, syntax<bk>>::type
```

When all `p1` ... `pn` evaluates to false

```cpp
try_<
  syntax<f>,
  catch_<e1, syntax<p1>, syntax<b1>>,
  // ...
  catch_<en, syntax<pn>, syntax<bn>>
>::type
```

is equivalent to

```cpp
make_monadic<exception_monad, g>::type
```

In all the above cases

```cpp
catch_c<ei, pi, bi>
```

is equivalent to

```cpp
catch_<ei, syntax<pi>, syntax<bi>>
```

For all `1 <= i <= n`.

## Example

```cpp
using boost::mpl::int_;
using namespace mpllibs::metamonad::name;

struct error_tag_1;
struct error_tag_2;

struct unknown_error_detected;

try_<
  syntax<may_fail2<may_fail1<int_<13>>>>,
  catch_c<e, is_tag<error_tag_1, e>, int_<11>>,
  catch_c<e, is_tag<error_tag_2, e>, e>,
  catch_c<e, true_, unknown_error_detected>
>
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)



