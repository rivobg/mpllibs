#ifndef MPLLIBS_PARSER_ACCEPT_WHEN_H
#define MPLLIBS_PARSER_ACCEPT_WHEN_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/util/unless_nothing.h>

#include <mpllibs/metaparse/util/compose.h>
#include <mpllibs/metaparse/util/lazy_eval_if.h>
#include <mpllibs/metaparse/util/lazy_equal_to.h>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/pair.hpp>

namespace mpllibs
{
  namespace metaparse
  {
    template <class p, class pred>
    struct accept_when
    {
      template <class S>
      struct apply :
        mpllibs::metaparse::util::unless_nothing<
          boost::mpl::apply<p, S>,
          mpllibs::metaparse::util::lazy_eval_if<
            boost::mpl::apply<
              mpllibs::metaparse::util::compose<
                pred,
                boost::mpl::quote1<boost::mpl::first>
              >,
              typename boost::mpl::apply<p, S>::type
            >,
            boost::mpl::apply<p, S>,
            mpllibs::metaparse::nothing
          >
        >
      {};
    };
  }
}

#endif
