// Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metaparse/impl/split_at_c.hpp>
#include <mpllibs/metaparse/string.hpp>

#include <boost/mpl/pair.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_split_at_c)
{
  using mpllibs::metaparse::impl::split_at_c;
  using mpllibs::metaparse::string;
  
  using boost::mpl::pair;

  using boost::is_same;

  typedef string<> empty;
  typedef string<'h','e','l','l','o'> hello;

  // test_split_in_the_middle
  BOOST_MPL_ASSERT((
    is_same<
      pair<string<'h','e','l'>, string<'l','o'> >,
      split_at_c<3, hello>::type
    >
  ));

  // test_split_at_the_beginning
  BOOST_MPL_ASSERT((is_same<pair<empty, hello>, split_at_c<0, hello>::type>));

  // test_split_at_the_end
  BOOST_MPL_ASSERT((is_same<pair<hello, empty>, split_at_c<5, hello>::type>));
}


