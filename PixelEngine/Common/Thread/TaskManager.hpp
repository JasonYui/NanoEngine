#pragma once
#include "PixelEngine/Common/Type/BasicType.hpp"
#include "PixelEngine/Common/Type/ArrayWrapper.hpp"
#include "PixelEngine/Common/IRuntimeModule.hpp"
#include "PixelEngine/Common/Thread/TaskPriority.hpp"
#include <thread>
#include <mutex>
#include <future>
#include <atomic>


namespace Pixel
{
    class TaskManager : IRuntimeModule
    {
    public:
        TaskManager();
        ~TaskManager();

        bool Init() final;
        bool Init(uint16_t threadSize);
        void Close() final;
        void Update(float dt);
        bool HasUnprocessTask(uint32_t threadId) const;
    
        template<typename Func, typename... Args>
        std::future<typename std::result_of<Func(Args...)>::type> AddTask(TaskPriority priority, Func&& func, Args&&... args);
    private:
        using PriorityTaskArray = Array<Queue<std::function<void()>>, (size_t)TaskPriority::_SIZE>; //$todo: try use TaskPriority::_SIZE

        void ProcessTask(uint32_t threadId);

        Vector<std::thread> m_Workers;

        std::mutex m_Mutex;

        std::condition_variable m_Condition;

        PriorityTaskArray m_TaskQueueArray;

        std::unique_ptr<PriorityTaskArray[]> m_ThreadPinnedTaskArray;

        std::atomic<bool> m_IsClosed{ false };

        uint16_t m_ThreadSize{ 1 };
    };

    template<typename Func, typename... Args>
    std::future<typename std::result_of<Func(Args...)>::type> TaskManager::AddTask(TaskPriority priority, Func&& func, Args&&... args)
    {
        using resultType = typename std::result_of<Func(Args...)>::type;

        std::shared_ptr<std::packaged_task<resultType()>> task = std::make_shared<std::packaged_task<resultType()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
            );

        std::future<resultType> res = task->get_future();
        std::unique_lock<std::mutex> lock(m_Mutex);
        if (m_IsClosed)
        {
            throw std::runtime_error("TaskManager is closed");
        }
        m_TaskQueueArray[size_t(priority)].emplace([task]() { (*task)(); });
        m_Condition.notify_one();

        return res;
    }
}