#ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SPINLOCK_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  ndnboost/detail/spinlock.hpp
//
//  Copyright (c) 2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  struct spinlock
//  {
//      void lock();
//      bool try_lock();
//      void unlock();
//
//      class scoped_lock;
//  };
//
//  #define BOOST_DETAIL_SPINLOCK_INIT <unspecified>
//

#include <ndnboost/config.hpp>
#include <ndnboost/smart_ptr/detail/sp_has_sync.hpp>

#if defined( BOOST_SP_USE_PTHREADS )
#  include <ndnboost/smart_ptr/detail/spinlock_pt.hpp>

#elif defined(__GNUC__) && defined( __arm__ ) && !defined( __thumb__ )
#  include <ndnboost/smart_ptr/detail/spinlock_gcc_arm.hpp>

#elif defined( BOOST_SP_HAS_SYNC )
#  include <ndnboost/smart_ptr/detail/spinlock_sync.hpp>

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#  include <ndnboost/smart_ptr/detail/spinlock_w32.hpp>

#elif defined(BOOST_HAS_PTHREADS)
#  include <ndnboost/smart_ptr/detail/spinlock_pt.hpp>

#elif !defined(BOOST_HAS_THREADS)
#  include <ndnboost/smart_ptr/detail/spinlock_nt.hpp>

#else
#  error Unrecognized threading platform
#endif

#endif // #ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_HPP_INCLUDED
