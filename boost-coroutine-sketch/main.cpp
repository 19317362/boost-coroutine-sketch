//
//  main.cpp
//  boost-coroutine-sketch
//
//  Created by Justin Walsh on 9/22/15.
//  Copyright (c) 2015 Justin Walsh. All rights reserved.
//

#include <iostream>
#include <boost/coroutine2/all.hpp>

int main(int argc, const char * argv[])
{
   using coroutine_t = boost::coroutines2::coroutine<int>;
   
   coroutine_t::pull_type source([&](coroutine_t::push_type& sink) {
      int first = 1, second = 1;
      sink(first);
      sink(second);
      for (int i = 0; i < 8; ++i) {
         int third = first + second;
         first = second;
         second = third;
         sink(third);
       }
   });
   
   for (auto i:source) {
      std::cout << i <<  " ";
   }
   
   return 0;
}
