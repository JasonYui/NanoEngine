#pragma once
#include <functional>
#include <future>
#include <memory>
#include "NanoEngine/Common/CommonGlobalContext.hpp"
#include "NanoEngine/Common/Thread/TaskManager.hpp"
#include "NanoEngine/Common/Thread/TaskPriority.hpp"

namespace Nano
{
    template<class T>
    class Task
    {
        using Func = std::function<T()>;

    public:
        Task() = delete;
        
        Task(const Func& func) :
            m_Func(func)
        {}

        Task(Func&& func) :
            m_Func(func)
        {}

        Task(Task&& task) noexcept : 
            m_Future(std::move(task.m_Future)),
            m_Func(std::move(task.m_Func))
        {}

        ~Task() = default;

        /*Task ContinueWith();*/
        void Wait()
        {
            if (m_Future.valid())
                m_Future.wait();
            else
                throw std::runtime_error("Task future is invalid");
        }

        T Result()
        {
            if (m_Future.valid())
                return m_Future.get();
            else
                throw std::runtime_error("Task future is invalid");
        }

        void Start()
        {
            m_Future = g_CommonGloablContext.m_TaskManager->AddTask(m_Func);
        }

        static Task Run(Func&& func, TaskPriority priority = TaskPriority::_NORMAL)
        {
            Task task = Task(std::forward<Func>(func));
            task.m_Future = g_CommonGloablContext.m_TaskManager->AddTask(priority, task.m_Func);
            return task;
        }
    private:
        friend class TaskManager;
        std::shared_future<T> m_Future;
        Func m_Func;
        TaskPriority m_Priority{TaskPriority::_NORMAL};
    };

    template<>
    class Task<void>
    {
        using Func = std::function<void()>;
    public:
        Task() = delete;
        Task(Func&& func) : 
            m_Func(func)
        {}

        Task(Task&& task) noexcept : 
            m_Future(std::move(task.m_Future)),
            m_Func(std::move(task.m_Func))
        {}

        ~Task() = default;

        void Wait()
        {
            if (m_Future.valid())
                m_Future.wait();
            else
                throw std::runtime_error("Task future is invalid");
        }

        static Task Run(Func&& func, TaskPriority priority = TaskPriority::_NORMAL)
        {
            Task task = Task(std::forward<Func>(func));
            task.m_Future = g_CommonGloablContext.m_TaskManager->AddTask(priority, task.m_Func);
            return task;
        }
    private:
        std::future<void> m_Future;
        Func m_Func;
    };
}