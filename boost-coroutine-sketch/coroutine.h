//
//  coroutine.h
//  boost-coroutine-sketch
//
//  Created by Justin Walsh on 9/24/15.
//  Copyright (c) 2015 Justin Walsh. All rights reserved.
//

#ifndef coroutine_h
#define coroutine_h

#include <boost/coroutine2/all.hpp>

template< typename T >
struct coroutine {
   typedef boost::coroutines2::detail::pull_coroutine<T> pull_type;
   typedef boost::coroutines2::detail::push_coroutine<T> push_type;
};

#endif
