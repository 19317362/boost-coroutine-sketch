//
//  fixsized_stack_pool.h
//  boost-coroutine-sketch
//
//  Created by Justin Walsh on 9/24/15.
//  Copyright (c) 2015 Justin Walsh. All rights reserved.
//

#ifndef boost_coroutine_sketch_fixsized_stack_pool_h
#define boost_coroutine_sketch_fixsized_stack_pool_h

#include <cstddef>
#include <cstdlib>
#include <new>
#include <stack>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

template< typename traitsT >
class fixedsize_stack_pool {
private:
#if defined(BOOST_USE_WINFIBERS)
   friend class execution_context;
#endif
   
   std::size_t     size_;
   std::size_t     count_;
   
   void*             pool_;
   std::stack<void*> stack_ptrs_;
   
   
public:
   typedef traitsT traits_type;
   
   fixedsize_stack_pool( std::size_t count, std::size_t size = traits_type::default_size() ) :
   count_(count), size_( size) {
      BOOST_ASSERT( traits_type::minimum_size() <= size_);
      BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= size_) );
      
      // Allocate our buffer and stack
      pool_ = std::malloc(count_ * size_);
      if (!pool_) throw std::bad_alloc();
      
      // Populate our ptr stack
      for (std::size_t i = 0; i < count_ * size_; i++) {
         std::size_t offset = i * size_;
         stack_ptrs_.push(&static_cast<char*>(pool_)[offset]);
      }
   }
   
   stack_context allocate() {
      if (stack_ptrs_.empty()) throw std::bad_alloc();
      
      void * vp = stack_ptrs_.top();
      stack_ptrs_.pop();
      
      stack_context sctx;
      sctx.size = size_;
      sctx.sp = static_cast< char * >( vp) + sctx.size;
#if defined(BOOST_USE_VALGRIND)
      sctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( sctx.sp, vp);
#endif
      return sctx;
   }
   
   void deallocate( stack_context & sctx) {
      BOOST_ASSERT( sctx.sp);
#if ! defined(BOOST_USE_WINFIBERS)
      BOOST_ASSERT( traits_type::minimum_size() <= sctx.size);
      BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= sctx.size) );
#endif
      
#if defined(BOOST_USE_VALGRIND)
      VALGRIND_STACK_DEREGISTER( sctx.valgrind_stack_id);
#endif
      
      void * vp = static_cast< char * >( sctx.sp) - sctx.size;
      stack_ptrs_.push(vp);
   }
};
   
}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif
