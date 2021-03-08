#pragma once
#include <mutex>
#include <future>

#include "common/fwd.hpp"
#include "common/type/memory_wrapper.hpp"
#include "common/type/queue_wrapper.hpp"
#include "common/parallelism/thread_pool.hpp"

namespace Nano
{
    class FIFOTaskScheduler
    {
    public:
        FIFOTaskScheduler();
        ~FIFOTaskScheduler();

        template<typename Func, typename... Args>
        std::future<typename std::invoke_result_t<Func, Args...>> AddTask(Func&& func, Args&&... args);
    private:
        void HandleTask(uint32_t threadId);

        static UniquePtr<ThreadPool> s_ThreadPool;
        
        std::mutex m_Mutex;
        std::condition_variable m_Condition;
        Queue<std::function<void()>> m_TaskQueue;
    };

    template<typename Func, typename... Args>
    std::future<typename std::invoke_result_t<Func, Args...>> FIFOTaskScheduler::AddTask(Func&& func, Args&&... args)
    {
        using TRet = typename std::invoke_result_t<Func, Args...>;

        std::shared_ptr<std::packaged_task<TRet()>> task = std::make_shared<std::packaged_task<TRet()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

        std::future<TRet> future = task->get_future();
        std::unique_lock<std::mutex> lock(m_Mutex);

        m_TaskQueue.emplace([task]() { (*task)(); });
        m_Condition.notify_one();

        return future;
    }

    extern UniquePtr<FIFOTaskScheduler> g_TaskScheduler;
}