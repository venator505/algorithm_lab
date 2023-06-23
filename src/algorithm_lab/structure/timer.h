#pragma once

#include <functional>
#include <queue>
#include <chrono>
#include <thread>
#include <utility>
#include <type_traits>
namespace yyds {

class Timer
{
private:
    using DelayFunc =
        std::pair<std::function<void()>,
                  std::chrono::time_point<std::chrono::high_resolution_clock>>;
    class TimerComparer
    {
    public:
        bool operator()(const DelayFunc& d1, const DelayFunc& d2)
        {
            return d1.second > d2.second;
        }
    };

public:
    void submit(
        std::function<void()> f,
        std::chrono::time_point<std::chrono::high_resolution_clock> point)
    {
        q.push(DelayFunc(f, point));
    }

    void run()
    {
        while (q.size())
        {
            if (q.size() &&
                q.top().second < std::chrono::high_resolution_clock::now())
            {
                auto task = q.top();
                q.pop();
                task.first();
            }
        }
    }

private:
    std::priority_queue<DelayFunc, std::vector<DelayFunc>, Timer::TimerComparer>
        q;
};
} // namespace yyds