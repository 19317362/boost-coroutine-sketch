cmake_minimum_required(VERSION 3.3)
project(boost_coroutine_sketch)

enable_language(ASM)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    boost-coroutine-sketch/coroutine.h
    boost-coroutine-sketch/fixedsize_stack_pool.h
    boost-coroutine-sketch/main.cpp
    context/include/boost/context/detail/config.hpp
    context/include/boost/context/detail/fcontext_arm.hpp
    context/include/boost/context/detail/fcontext_arm_mac.hpp
    context/include/boost/context/detail/fcontext_arm_win.hpp
    context/include/boost/context/detail/fcontext_i386.hpp
    context/include/boost/context/detail/fcontext_i386_win.hpp
    context/include/boost/context/detail/fcontext_mips.hpp
    context/include/boost/context/detail/fcontext_ppc.hpp
    context/include/boost/context/detail/fcontext_sparc.hpp
    context/include/boost/context/detail/fcontext_x86_64.hpp
    context/include/boost/context/detail/fcontext_x86_64_win.hpp
    context/include/boost/context/detail/invoke.hpp
    context/include/boost/context/posix/protected_fixedsize_stack.hpp
    context/include/boost/context/posix/segmented_stack.hpp
    context/include/boost/context/windows/protected_fixedsize_stack.hpp
    context/include/boost/context/all.hpp
    context/include/boost/context/execution_context.hpp
    context/include/boost/context/fcontext.hpp
    context/include/boost/context/fixedsize_stack.hpp
    context/include/boost/context/protected_fixedsize_stack.hpp
    context/include/boost/context/segmented_stack.hpp
    context/include/boost/context/stack_context.hpp
    context/include/boost/context/stack_traits.hpp
    context/src/asm/jump_x86_64_sysv_elf_gas.S
    context/src/asm/make_x86_64_sysv_elf_gas.S
    context/src/posix/stack_traits.cpp
    context/src/execution_context.cpp
    coroutine2/include/boost/coroutine2/detail/config.hpp
    coroutine2/include/boost/coroutine2/detail/coroutine.hpp
    coroutine2/include/boost/coroutine2/detail/forced_unwind.hpp
    coroutine2/include/boost/coroutine2/detail/pull_control_block.hpp
    coroutine2/include/boost/coroutine2/detail/pull_coroutine.hpp
    coroutine2/include/boost/coroutine2/detail/push_control_block.hpp
    coroutine2/include/boost/coroutine2/detail/push_coroutine.hpp
    coroutine2/include/boost/coroutine2/detail/state.hpp
    coroutine2/include/boost/coroutine2/all.hpp
    coroutine2/include/boost/coroutine2/coroutine.hpp
    coroutine2/include/boost/coroutine2/fixedsize_stack.hpp
    coroutine2/include/boost/coroutine2/protected_fixedsize_stack.hpp
    coroutine2/include/boost/coroutine2/segmented_stack.hpp)

include_directories(boost-coroutine-sketch)
include_directories(context/include)
include_directories(coroutine2/include)

add_executable(boost_coroutine_sketch ${SOURCE_FILES})

find_package(Boost COMPONENTS system thread REQUIRED)
target_link_libraries(boost_coroutine_sketch ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
