#ifndef MPLLIBS_METAMONAD_TRY_HPP
#define MPLLIBS_METAMONAD_TRY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metamonad/do_.hpp>
#include <mpllibs/metamonad/let.hpp>
#include <mpllibs/metamonad/exception.hpp>
#include <mpllibs/metamonad/get_data.hpp>

#include <boost/mpl/tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>

#include <boost/type_traits/is_same.hpp>

/*
 * Catching exceptions happens by using
 *   TRY<...>
 *     ::catch_<Tag1, Name1>
 *       ::apply<Body1>
 *     ::catch_<Tag2, Name2>
 *       ::apply<Body2>
 * instead of
 *   TRY<...>
 *     ::catch_<Tag1, Name1, Body1>
 *     ::catch_<Tag2, Name2, Body2>
 * to avoid ambiguity related to
 *  http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#147
 * caused by TRY<...>::catch_<...>::catch_<...> patterns.
 */

namespace mpllibs
{
  namespace metamonad
  {
    #ifdef MPLLIBS_TRY
      #error MPLLIBS_TRY already defined
    #endif
    #define MPLLIBS_TRY mpllibs::metamonad::try_

    struct catch_any
    {
      typedef catch_any type;
    };

    namespace impl
    {
      // evaluates result lazily
      template <class Result>
      struct skip_further_catches
      {
        typedef Result type;
        
        template <class ExceptionTag, class Name>
        struct catch_
        {
          template <class Body>
          struct apply : skip_further_catches {};
        };
      };
      
      template <class Result>
      struct lazy_skip_further_catches :
        skip_further_catches<typename Result::type>
      {};
      
      template <class Exception>
      struct was_exception
      {
        typedef Exception type;
        
        template <class ExceptionTag, class Name>
        struct catch_
        {
        private:
          typedef typename get_data<Exception>::type _exception_data;

          typedef
            typename boost::mpl::tag<_exception_data>::type _exception_data_tag;
        public:
          template <class Body>
          struct apply :
            boost::mpl::if_<
              boost::mpl::or_<
                boost::is_same<ExceptionTag, _exception_data_tag>,
                boost::is_same<ExceptionTag, catch_any>
              >,
              lazy_skip_further_catches<
                typename let<Name, _exception_data, Body>::type
              >,
              was_exception
            >::type
          {};
        };
      };
    }

    template <
      BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
        MPLLIBS_DO_MAX_ARGUMENT,
        class E,
        unused_do_argument
      )
    >
    struct try_ :
      boost::mpl::if_<
        typename boost::is_same<
          exception_tag,
          typename boost::mpl::tag<
            typename MPLLIBS_DO<exception_monad>::template apply<
              BOOST_PP_ENUM_PARAMS(MPLLIBS_DO_MAX_ARGUMENT, E)
            >::type
          >::type
        >::type,
        mpllibs::metamonad::impl::was_exception<
          typename MPLLIBS_DO<exception_monad>::template apply<
            BOOST_PP_ENUM_PARAMS(MPLLIBS_DO_MAX_ARGUMENT, E)
          >::type
        >,
        mpllibs::metamonad::impl::skip_further_catches<
          typename MPLLIBS_DO<exception_monad>::template apply<
            BOOST_PP_ENUM_PARAMS(MPLLIBS_DO_MAX_ARGUMENT, E)
          >::type
        >
      >::type
    {};
  }
}

#endif

