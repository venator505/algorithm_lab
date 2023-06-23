#include <chrono>
#include <cstddef>
#include <exception>
#include <iostream>
#include "algorithm_lab/structure/timer.h"
#include "gtest/gtest.h"
#include <thread>
TEST(Timer, Timer)
{
    yyds::Timer timer;
    using namespace std::chrono_literals;
    timer.submit([&]() { std::cout << "延迟3s后出现\n"; },
                 std::chrono::high_resolution_clock::now() + 3s);
    timer.submit([&]() { std::cout << "延迟1s后出现\n"; },
                 std::chrono::high_resolution_clock::now() + 1s);
    timer.submit([&]() { std::cout << "延迟5s后出现\n"; },
                 std::chrono::high_resolution_clock::now() + 5s);
    timer.run();
}