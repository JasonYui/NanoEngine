#include "common/parallelism/task_scheduler.hpp"

namespace Nano
{
    int size = std::thread::hardware_concurrency();

    UniquePtr<ThreadPool> FIFOTaskScheduler::s_ThreadPool = std::make_unique<ThreadPool>(size);

    UniquePtr<FIFOTaskScheduler> g_TaskScheduler = std::make_unique<FIFOTaskScheduler>();

    FIFOTaskScheduler::FIFOTaskScheduler()
    {
        s_ThreadPool->Init(std::bind(&FIFOTaskScheduler::HandleTask, this, std::placeholders::_1));
    }

    FIFOTaskScheduler::~FIFOTaskScheduler()
    {
        s_ThreadPool->Close();
    }

    void FIFOTaskScheduler::HandleTask(uint32_t threadId)
    {
        for (;;)
        {
            LOG_INFO_DEBUG("thread {0} running", threadId);
            std::function<void()> task;
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_Condition.wait(lock, [this] 
            {
                return !m_TaskQueue.empty();
            });
            LOG_INFO_DEBUG("thread {0:d} handle task", threadId);
            task = std::move(m_TaskQueue.front());
            m_TaskQueue.pop();
            lock.unlock();

            task();
        }
    }
}