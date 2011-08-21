// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/util/digit_to_int.hpp>

#include "common.hpp"

#include <mpllibs/metatest/test.hpp>
#include <mpllibs/metatest/has_type.hpp>

#include <mpllibs/metamonad/do_try.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply_wrap.hpp>

using mpllibs::metatest::suite_path;
using mpllibs::metatest::has_type;

using mpllibs::metaparse::util::digit_to_int;
using mpllibs::metaparse::error_tag;

using mpllibs::metamonad::do_try;

using boost::mpl::equal_to;
using boost::mpl::apply_wrap1;

namespace
{
  const suite_path suite = suite_path("util")("digit_to_int");

  typedef has_type<digit_to_int> test_has_type;

  typedef equal_to<apply_wrap1<digit_to_int, char_0>::type, int0> test0;

  typedef equal_to<apply_wrap1<digit_to_int, char_9>::type, int9> test9;
  
  struct x;
  
  typedef
    equal_to<
      do_try<
        apply_wrap1<digit_to_int, char_x>
      >
      ::catch_<error_tag, x>::apply<int13>
      ::type,
      int13
    >
    test_error;
}

MPLLIBS_ADD_TEST(suite, test_has_type)
MPLLIBS_ADD_TEST(suite, test0)
MPLLIBS_ADD_TEST(suite, test9)
MPLLIBS_ADD_TEST(suite, test_error)

