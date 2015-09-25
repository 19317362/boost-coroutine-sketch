//
//  main.cpp
//  boost-coroutine-sketch
//
//  Created by Justin Walsh on 9/22/15.
//  Copyright (c) 2015 Justin Walsh. All rights reserved.
//

#include <iostream>

#include "coroutine.h"
#include "fixedsize_stack_pool.h"

int main(int argc, const char * argv[])
{
   //boost::context::fixedsize_stack_pool<boost::context::stack_traits> stack_pool(100);
   
   coroutine<int>::pull_type fibonachi([&](coroutine<int>::push_type& yield) {
      int first = 1, second = 1;
      yield(first);
      yield(second);
      for (int i = 0; i < 20; ++i) {
         int third = first + second;
         first = second;
         second = third;
         yield(third);
       }
   });
   
   for (auto i:fibonachi) {
      std::cout << i <<  " ";
   }
   
   return 0;
}
